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

RadioData::RadioData()
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
  if(!labels.contains(label))
    labels.append(label);
}

void RadioData::deleteLabel(QString label)
{
  // Remove labels in the models
  for(auto& model : models) {
    QStringList modelLabels = QString(model.labels).split(',',Qt::SkipEmptyParts);
    modelLabels.removeAll(label);
    strcpy(model.labels, QString(modelLabels.join(',')).toLocal8Bit().data());
  }

  // Remove the label from the global list
  labels.removeAll(label);

  // If no labels remain, add a Favorites one
  if(!labels.size()) {
    addLabel(tr("Favorites"));
  }
}

bool RadioData::renameLabel(QString from, QString to)
{
  bool success = true;
  int lengthdiff = to.size() - from.size();

  // Check that rename is possible, not too long
  for(auto& model : models) {
    if((int)strlen(model.labels) + lengthdiff > (int)sizeof(model.labels) - 1) {
      success = false;
    }
  }
  if(success) {
    for(auto& model : models) {
      QStringList modelLabels = QString(model.labels).split(',',Qt::SkipEmptyParts);
      int ind = modelLabels.indexOf(from); // TOOD: Make sure it will fit
      if(ind != -1) {
        modelLabels.replace(ind, to);
        strcpy(model.labels, QString(modelLabels.join(',')).toLocal8Bit().data());
      }
    }
    int ind = labels.indexOf(from);
    if(ind != -1) {
      labels.replace(ind, to);
    }
  }
  return success;
}

bool RadioData::renameLabel(int index, QString to)
{
  if(index >= labels.size()) return false;
  QString from = labels.at(index);
  return renameLabel(from, to);
}

bool RadioData::addLabelToModel(int index, QString label)
{
  if(index >= models.size()) return false;

  char *modelLabelCsv = models[index].labels;
  // Make sure it will fit
  if(strlen(modelLabelCsv) + label.size() + 1 < sizeof(models[index].labels)-1) {
    QStringList modelLabels = QString(modelLabelCsv).split(',',Qt::SkipEmptyParts);
    if(!modelLabels.contains(label)) {
      modelLabels.append(label);
      strcpy(models[index].labels, QString(modelLabels.join(',')).toLocal8Bit().data());
      return true;
    }
  }
  return false;
}

bool RadioData::removeLabelFromModel(int index, QString label)
{
  if(index >= models.size()) return false;

  char *modelLabelCsv = models[index].labels;
  QStringList modelLabels = QString(modelLabelCsv).split(',',Qt::SkipEmptyParts);
  if(modelLabels.contains(label)) {
    modelLabels.removeAll(label);
    strcpy(models[index].labels, QString(modelLabels.join(',')).toLocal8Bit().data());
    return true;
  }
  return false;
}
