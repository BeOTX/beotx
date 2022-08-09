#pragma once

#include <QObject>
#include <QList>
#include <QAbstractItemModel>
#include <QItemSelectionModel>

#include "radiodata.h"

class RadioData;

class LabelsModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  LabelsModel(QItemSelectionModel *selectionModel, RadioData *radioData, QObject *parent = nullptr);
  ~LabelsModel();
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private slots:
  void buildLabelsList();
  void modelsSelectionChanged();

private:
  QItemSelectionModel *modelsSelection;
  RadioData *radioData;
  int selectedModel;
  QList<QModelIndex> modelIndices;
};

