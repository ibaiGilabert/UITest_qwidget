#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QVBoxLayout>

//#include "ibusiness.h"
#include "modelsections.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /*!
   * \brief MainWindow
   * \param parent
   */
  MainWindow(QWidget *parent = nullptr);
  /*!
   * \brief MainWindow
   * \param parent
   */
  ~MainWindow();

  /*!
   * \brief InitializeModel
   */
  void InitializeModel();

  /*!
   * \brief InitializeUI
   */
  void InitializeUI();

 private slots:
  /*!
   * \brief on_button_accept_clicked
   */
  void on_button_accept_clicked();
  /*!
   * \brief OnDataChanged
   */
  void OnDataChanged(const QModelIndex &, const QModelIndex &,
                     const QVector<int> &);
  /*!
   * \brief UpdateDashboard
   */
  void UpdateDashboard();

  /*!
   * \brief UpdateTableFaults
   * \param section
   */
  void UpdateTableFaults(const data_model::Section *section);
 signals:
  /*!
   * \brief NewResult
   */
  void NewResult();

 private:
  /*!
   * \brief AddQWidgetSectionLabel
   * \param layout
   * \param num_elements
   * \param apply_stylesheet
   */
  void AddQWidgetSectionLabel(QVBoxLayout *layout, int num_elements,
                              bool apply_stylesheet);
  /*!
   * \brief AddQWidgetSectionProgressBar
   * \param layout
   * \param num_elements
   * \param elasticity
   */
  void AddQWidgetSectionProgressBar(QVBoxLayout *layout, int num_elements,
                                    int elasticity);
  /*!
   * \brief ConnectSignals
   */
  void ConnectSignals();
  /*!
   * \brief InitializeLabelPixmap
   * \param resource_id
   * \param label_id
   */
  void InitializeLabelPixmap(const std::string &resource_id, QLabel *label_id);

 private:
  /*!
   * \brief ui
   */
  Ui::MainWindow *ui;
  /*!
   * \brief model_
   */
  ModelSections *model_;
};
#endif  // MAINWINDOW_H
