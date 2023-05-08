/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "radiodata.h"
#include "radiodataconversionstate.h"
#include "eeprominterface.h"

RadioData::RadioData() :
  sortOrder(0)
{
  models.resize(getCurrentFirmware()->getCapability(Models));
}

void RadioData::setCurrentModel(unsigned int index)
{
  generalSettings.currModelIndex = index;
  if (index < models.size()) {
    strcpy(generalSettings.currModelFilename, models[index].filename);
  }
}

void RadioData::fixModelFilename(unsigned int index)
{
  ModelData & model = models[index];
  QString filename(model.filename);
  const bool hasSDCard = Boards::getCapability(getCurrentFirmware()->getBoard(), Board::HasSDCard);
  bool ok = hasSDCard ? filename.endsWith(".yml") : filename.endsWith(".bin");
  if (ok) {
    if (filename.startsWith("model") && filename.mid(5, filename.length()-9).toInt() > 0) {
      ok = false;
    }
  }
  if (ok) {
    for (unsigned i=0; i<index; i++) {
      if (strcmp(models[i].filename, model.filename) == 0) {
        ok = false;
        break;
      }
    }
  }
  if (!ok) {
    sprintf(model.filename, "model%d.%s", index + 1, hasSDCard ? "yml" : "bin");
  }
}

void RadioData::fixModelFilenames()
{
  for (unsigned int i=0; i<models.size(); i++) {
    fixModelFilename(i);
  }
  setCurrentModel(generalSettings.currModelIndex);
}

QString RadioData::getNextModelFilename()
{
  const bool hasSDCard = Boards::getCapability(getCurrentFirmware()->getBoard(), Board::HasSDCard);
  char filename[sizeof(ModelData::filename)];
  int index = 0;
  bool found = true;
  while (found) {
    sprintf(filename, "model%d.%s", ++index, hasSDCard ? "yml" : "bin");
    found = false;
    for (unsigned int i=0; i<models.size(); i++) {
      if (strcmp(filename, models[i].filename) == 0) {
        found = true;
        break;
      }
    }
  }
  return filename;
}

void RadioData::convert(RadioDataConversionState & cstate)
{
  generalSettings.convert(cstate.withModelIndex(-1));

  for (unsigned i=0; i<models.size(); i++) {
    models[i].convert(cstate.withModelIndex(i));
  }

  if (IS_FAMILY_HORUS_OR_T16(cstate.toType)) {
    fixModelFilenames();
  }

  // ensure proper number of model slots
  if (getCurrentFirmware()->getCapability(Models) && getCurrentFirmware()->getCapability(Models) != (int)models.size()) {
    models.resize(getCurrentFirmware()->getCapability(Models));
  }
}

void RadioData::addLabel(QString label)
{
  label = unEscapeCSV(label);
  // Truncate possible UTF-8 to 16char maximum
  QByteArray output = label.toUtf8();
  if (output.size() > LABEL_LENGTH) {
      int truncateAt = 0;
      for (int i = LABEL_LENGTH; i > 0; i--) {
          if ((output[i] & 0xC0) != 0x80) {
              truncateAt = i;
              break;
          }
      }
      output.truncate(truncateAt);
  }
  label = QString(output);
  if (labels.indexOf(label) == -1)
    labels.append(label);
}

bool RadioData::deleteLabel(QString label)
{
  bool deleted = false;

  // Remove labels in the models
  for(auto& model : models) {
    QStringList modelLabels = fromCSV(QString::fromUtf8(model.labels));
    if (modelLabels.indexOf(label) >= 0) {
      deleted = true;
      modelLabels.removeAll(label);
    }
    strcpy(model.labels, toCSV(modelLabels).toUtf8().data());
  }

  // Remove the label from the global list
  labels.removeAll(label);

  // If no labels remain, add a Favorites one
  if (!labels.size()) {
    addLabel(tr("Favorites"));
  }
  return deleted;
}

bool RadioData::deleteLabel(int index)
{
  if (index >= labels.size()) return false;
  QString modelLabel = labels.at(index);
  return deleteLabel(modelLabel);
}

bool RadioData::renameLabel(QString from, QString to)
{
  bool success = true;
  QString csvFrom = escapeCSV(from);
  QString csvTo = escapeCSV(to);
  int lengthdiff = csvTo.size() - csvFrom.size();

  // Check that rename is possible (Rename won't cause too long of a string)
  for(auto& model : models) {
    if (RadioData::fromCSV(model.labels).indexOf(from) != -1) {
      if ((int)strlen(model.labels) + lengthdiff > (int)sizeof(model.labels) - 1) {
        success = false;
        throw std::length_error(model.name);
        break;
      }
    }
  }
  if (success) {
    for(auto& model : models) {
      QStringList modelLabels = QString(model.labels).split(',',QString::SkipEmptyParts);
      int ind = modelLabels.indexOf(csvFrom);
      if (ind != -1) {
        modelLabels.replace(ind, csvTo);
        QString outputcsv = QString(modelLabels.join(','));
        if (outputcsv.toUtf8().size() < (int)sizeof(model.labels)) {
          strcpy(model.labels, outputcsv.toUtf8().data());
        } else { // Shouldn't ever get here, from check above
          success = false;
          throw std::length_error(model.name);
          break;
        }
      }
    }
    int ind = labels.indexOf(from);
    if (ind != -1) {
      labels.replace(ind, to);
    }
  }
  return success;
}

bool RadioData::renameLabel(int index, QString to)
{
  if (index >= labels.size()) return false;
  QString from = labels.at(index);
  return renameLabel(from, to);
}

void RadioData::swapLabel(int indFrom, int indTo)
{
  if(abs(indFrom - indTo) > 1 ||
      indFrom >= labels.size() ||
      indTo >= labels.size() ||
      indFrom < 0 ||
      indTo < 0)
    return;
  QString tmplbl = labels.at(indFrom);
  labels.replace(indFrom, labels.at(indTo));
  labels.replace(indTo, tmplbl);
}

bool RadioData::addLabelToModel(int index, QString label)
{
  if ((unsigned int)index >= models.size()) return false;
  label = escapeCSV(label);

  char *modelLabelCsv = models[index].labels;
  // Make sure it will fit
  if (strlen(modelLabelCsv) + label.size() + 1 < sizeof(models[index].labels)-1) {
    QStringList modelLabels = QString::fromUtf8(modelLabelCsv).split(',',QString::SkipEmptyParts);
    if (modelLabels.indexOf(label) == -1) {
      modelLabels.append(label);
      strcpy(models[index].labels, QString(modelLabels.join(',')).toUtf8().data());
      return true;
    }
  }
  throw std::length_error(models[index].name);
  return false;
}

bool RadioData::removeLabelFromModel(int index, QString label)
{
  if ((unsigned int)index >= models.size()) return false;

  QStringList lbls = fromCSV(QString::fromUtf8(models[index].labels));
  if (lbls.indexOf(label) >= 0) {
    lbls.removeAll(label);
    strcpy(models[index].labels, toCSV(lbls).toUtf8().data());
    return true;
  }
  return false;
}

void RadioData::addLabelsFromModels()
{
  for(const auto &model: models) {
    QStringList labels = QString(model.labels).split(',',QString::SkipEmptyParts);
    foreach(QString label, labels) {
      addLabel(label);
    }
  }
}

QStringList RadioData::fromCSV(const QString &csv)
{
  QStringList lbls = QString(csv).split(',',QString::SkipEmptyParts);
  for(QString &label: lbls) {
    label = unEscapeCSV(label);
  }
  return lbls;
}

QString RadioData::toCSV(QStringList lbls)
{
  for(QString &label: lbls) {
    label = escapeCSV(label);
  }
  return lbls.join(',');
}

QString RadioData::escapeCSV(QString str)
{
  str.replace("/","//");
  str.replace(",","/c");
  return str;
}

QString RadioData::unEscapeCSV(QString str)
{
  str.replace("/c",",");
  str.replace("//","/");
  return str;
}
