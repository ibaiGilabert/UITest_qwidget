#ifndef MODELSECTIONS_H
#define MODELSECTIONS_H

#include <QAbstractItemModel>
#include <memory>

#ifdef USE_MOCK_MODEL
#include "mocks/mockbusiness.h"
#else
/* add here your real data Wrapper class*/
#endif

/*!
 * \brief The ModelSections class
 */
class ModelSections : public /*QAbstractItemModel*/ QAbstractListModel {
  Q_OBJECT

 public:
  /*!
   * \brief ModelSections
   * \param parent
   */
  explicit ModelSections(QObject *parent = nullptr);

  // Header:
  //  QVariant headerData(int section, Qt::Orientation orientation,
  //                      int role = Qt::DisplayRole) const override;

  // Basic functionality:
  //  QModelIndex index(int row, int column,
  //                    const QModelIndex &parent = QModelIndex()) const
  //                    override;
  //  QModelIndex parent(const QModelIndex &index) const override;

  /*!
   * \brief rowCount
   * \param parent
   * \return
   */
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  //  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  /*!
   * \brief data
   * \param index
   * \param role
   * \return
   */
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  /*!
   * \brief GetAdquisition
   * \return
   */
  const data_model::Adquisition *GetAdquisition() {
    return business_->GetAdquisition();
  }

 public slots:
  /*!
   * \brief OnNewResult
   */
  void OnNewResult();

 private:
  /*!
   * \brief InitializeDataModel
   */
  void InitializeDataModel();

 private:
  /*!
   * \brief business_
   */
  std::unique_ptr<IBusiness> business_;
};

// Q_DECLARE_METATYPE(model::SectionAlpha);
// Q_DECLARE_METATYPE(model::Adquisition);

#endif  // MODELSECTIONS_H
