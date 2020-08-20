#include "modelsections.h"

#include <QDebug>

ModelSections::ModelSections(QObject *parent) : QAbstractListModel(parent) {
  InitializeDataModel();
}

void ModelSections::InitializeDataModel() {
  // Initialize Business Logic
#ifdef USE_MOCK_MODEL
  business_ = std::make_unique<MockBusiness>();
#else
  /* add here your real data Wrapper */
#endif
  qDebug() << "Model created! with: " << business_->GetNumSection()
           << " elements";
}

// QVariant ModelSections::headerData(int section,
//                                        Qt::Orientation orientation,
//                                        int role) const {
//  if (role == Qt::DisplayRole) {
//    if (orientation == Qt::Horizontal) {
//      switch (section) {
//        case 0:
//          return QString("first");
//        case 1:
//          return QString("second");
//        case 2:
//          return QString("third");
//      }
//    }
//  }
//  return QVariant();
//}

// QModelIndex ModelSections::index(int row, int column, const QModelIndex
// &parent) const
//{
//    // FIXME: Implement me!
//}

// QModelIndex ModelSections::parent(const QModelIndex &index) const
//{
//    return index(row, pare
// }

int ModelSections::rowCount(const QModelIndex &parent) const {
  (void)parent;
  //  qDebug() << "parent?" << (parent.isValid() ? "TRUE" : "FALSE");
  //  if (!parent.isValid()) {
  //    return 0;
  //  }

  //  qDebug() << "Called getNumSection: " << business_->getNumSection();
  return business_->GetNumSection();

  //  return parent.row();
  // FIXME: Implement me!
}

// int ModelSections::columnCount(const QModelIndex &parent) const {
//  if (!parent.isValid()) {
//    return 0;
//  }

//  // FIXME: Implement me!
//}

// bool ModelSections::hasChildren(const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//}

// bool ModelSections::canFetchMore(const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//    return false;
//}

// void ModelSections::fetchMore(const QModelIndex &parent)
//{
//    // FIXME: Implement me!
//}

QVariant ModelSections::data(const QModelIndex &index, int role) const {
  qDebug() << "index: " << (index.isValid() ? "TRUE" : "FALSE");
  if (!index.isValid()) {
    return QVariant();
  }

  if (index.row() >= static_cast<int>(business_->GetNumSection())) {
    return QVariant();
  }

  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    qDebug() << "called Data! (index: " << index.row() << "," << index.column()
             << "), role: " << role;
    const data_model::Section *it = business_->GetSection(index.row());
    if (it->GetSectionType() == data_model::Section::SectionType::kAlpha) {
      //      qDebug() << "\tAlpha!";
      const data_model::SectionAlpha *alpha =
          dynamic_cast<const data_model::SectionAlpha *>(it);
      return QString::number(
                 static_cast<int>(alpha->GetCDimElement(index.row())->type_))
          .append(QString::fromStdString(
              data_model::ResultCode::kResultCodes
                  [alpha->GetCDimElement(index.row())->value_]));
      //      return alpha;
    } else {
      //      qDebug() << "\tBeta";
    }

    return business_->GetSection(index.row());
  }

  return QVariant();
}

void ModelSections::OnNewResult() {
  qDebug() << "Ask for a new Adquisition to be shown";
  // assume synchronous update
  business_->ProcessNewAdquisition();
  // notify manual change
  emit dataChanged(createIndex(0, 0), createIndex(rowCount(), 0));
}
