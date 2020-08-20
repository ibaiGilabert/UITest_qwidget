#include "mainwindow.h"

#include <QDebug>

//#include "qwidgetsection.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->showMaximized();

  InitializeModel();

  InitializeUI();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::InitializeModel() {
  model_ = new ModelSections(this);
  //  ui->table_faults_model->setModel(model_);
  //  ui->cl_view_sections->setModel(model_);

  ConnectSignals();
}

void MainWindow::InitializeUI() {
  {  // Labels
    // Outer surface
    this->InitializeLabelPixmap(":/resources/images/qsix_sp_inner.png",
                                ui->lbl_inner_surface);
    // Inner surface
    this->InitializeLabelPixmap(":/resources/images/qsix_sp_outer.png",
                                ui->lbl_outer_surface);
    // Lateral surface
    this->InitializeLabelPixmap(":/resources/images/qsix_sp_sidewalls.png",
                                ui->lbl_lateral_surface);
    // Logo
    this->InitializeLabelPixmap(":/resources/images/1200px-No-logo.svg",
                                ui->lbl_logo);
  }
}

void MainWindow::OnDataChanged(const QModelIndex &, const QModelIndex &,
                               const QVector<int> &) {
  UpdateDashboard();
}

void MainWindow::UpdateDashboard() {
  const data_model::Adquisition *result = model_->GetAdquisition();

  int total_c_dim = 0;
  int total_edges = 0;
  int total_defects = 0;

  int num_betas = 0;
  int total_endurance = 0;
  int total_elasticity = 0;

  QHBoxLayout *main_layout = new QHBoxLayout(ui->scrollAreaWidgetContents);
  main_layout->addLayout(new QVBoxLayout(ui->scrollArea_sections));
  ui->scrollArea_sections->setWidget(ui->scrollAreaWidgetContents);
  ui->scrollArea_sections->setWidgetResizable(true);

  for (size_t i = 0; i < result->size(); ++i) {
    QVBoxLayout *layout = new QVBoxLayout(ui->scrollArea_sections);
    layout->setMargin(0);
    layout->setSpacing(0);
    switch (result->at(i)->GetSectionType()) {
      case data_model::Section::SectionType::kAlpha: {
        const data_model::SectionAlpha *alpha =
            dynamic_cast<const data_model::SectionAlpha *>(result->at(i).get());
        AddQWidgetSectionLabel(layout, alpha->GetCDimListSize(), true);
        AddQWidgetSectionLabel(layout, alpha->GetEdgeListSize(), true);
        AddQWidgetSectionLabel(layout, alpha->GetDefectListSize(), true);
        AddQWidgetSectionLabel(layout, i, false);

        main_layout->addLayout(layout);

        // counters
        total_c_dim += alpha->GetCDimListSize();
        total_edges += alpha->GetEdgeListSize();
        total_defects += alpha->GetDefectListSize();
      } break;
      default:  // model::Section::SectionType::kBeta:
      {
        const data_model::SectionBeta *beta =
            dynamic_cast<const data_model::SectionBeta *>(result->at(i).get());
        AddQWidgetSectionProgressBar(layout, 100 * beta->GetEndurance(),
                                     100 * beta->GetElasticity());
        AddQWidgetSectionLabel(layout, i, false);

        main_layout->addLayout(layout);

        // counters;
        total_endurance += 100 * beta->GetEndurance();
        total_elasticity += 100 * beta->GetElasticity();
        ++num_betas;

      } break;
    }
  }

  {  // outer surface
     // c_dim
    ui->lbl_c_dim_num->setFrameShape(QFrame::Shape::Box);
    ui->lbl_c_dim_num->setFrameShadow(QFrame::Shadow::Raised);
    ui->lbl_c_dim_num->setStyleSheet(
        (total_c_dim > 0 ? "background-color:rgb(255, 0, 0); color: 'white'"
                         : "background-color:rgb(0, 255, 0); color: 'white'"));
    ui->lbl_c_dim_num->setText(QString::number(total_c_dim));
    // edges
    ui->lbl_edges_num->setFrameShape(QFrame::Shape::Box);
    ui->lbl_edges_num->setFrameShadow(QFrame::Shadow::Raised);
    ui->lbl_edges_num->setStyleSheet(
        (total_edges > 0 ? "background-color:rgb(255, 0, 0); color: 'white'"
                         : "background-color:rgb(0, 255, 0); color: 'white'"));
    ui->lbl_edges_num->setText(QString::number(total_edges));
    // defects
    ui->lbl_defects_num->setFrameShape(QFrame::Shape::Box);
    ui->lbl_defects_num->setFrameShadow(QFrame::Shadow::Raised);
    ui->lbl_defects_num->setStyleSheet((
        total_defects > 0 ? "background-color:rgb(255, 0, 0); color: 'white'"
                          : "background-color:rgb(0, 255, 0); color: 'white'"));
    ui->lbl_defects_num->setText(QString::number(total_defects));
    // # sections
    ui->lbl_sections_num->setText(QString::number(result->size()));
  }
  {  // inner surface
     // edges
    ui->lbl_edges_num_inner->setFrameShape(QFrame::Shape::Box);
    ui->lbl_edges_num_inner->setFrameShadow(QFrame::Shadow::Raised);
    ui->lbl_edges_num_inner->setStyleSheet(
        (total_edges > 0 ? "background-color:rgb(255, 0, 0); color: 'white'"
                         : "background-color:rgb(0, 255, 0); color: 'white'"));
    ui->lbl_edges_num_inner->setText(QString::number(total_edges));
    // defects
    ui->lbl_defects_num_inner->setFrameShape(QFrame::Shape::Box);
    ui->lbl_defects_num_inner->setFrameShadow(QFrame::Shadow::Raised);
    ui->lbl_defects_num_inner->setStyleSheet((
        total_defects > 0 ? "background-color:rgb(255, 0, 0); color: 'white'"
                          : "background-color:rgb(0, 255, 0); color: 'white'"));
    ui->lbl_defects_num_inner->setText(QString::number(total_defects));
    // # sections
    ui->lbl_sections_num_inner->setText(QString::number(result->size()));
  }
  {  // lateral surface
    ui->bar_lateral_endurance->setValue(total_endurance / num_betas);
    ui->bar_lateral_elasticity->setValue(total_elasticity / num_betas);
    // # sections
    ui->lbl_sections_num_lateral->setText(QString::number(result->size()));
  }

  // fill table faults with the first 'alpha' section
  const data_model::SectionAlpha *first_alpha = nullptr;
  for (size_t i = 0; first_alpha == nullptr && i < result->size(); ++i) {
    first_alpha =
        dynamic_cast<const data_model::SectionAlpha *>(result->at(i).get());
  }
  // element found, show its ResultCode at the lateral bar
  if (first_alpha) {
    UpdateTableFaults(first_alpha);
  }
}

void MainWindow::UpdateTableFaults(const data_model::Section *section) {
  switch (section->GetSectionType()) {
    case data_model::Section::SectionType::kAlpha: {
      const data_model::SectionAlpha *section_alpha =
          dynamic_cast<const data_model::SectionAlpha *>(section);

      int r = section_alpha->GetCDimListSize() +
              section_alpha->GetEdgeListSize() +
              section_alpha->GetDefectListSize();
      ui->table_faults_view->setRowCount(r);
      ui->table_faults_view->setColumnCount(3);
      ui->table_faults_view->setHorizontalHeaderLabels(
          QStringList({"CODE", "DESCRIPTION", "ERROR TYPE"}));
      ui->table_faults_view->horizontalHeader()->setSectionResizeMode(
          QHeaderView::Interactive);
      //      ui->table_faults_view->setSelectionBehavior(QAbstractItemView::SelectRows);
      //      ui->table_faults_view->setSelectionMode(QAbstractItemView::SingleSelection);
      size_t m = 0;
      // c_dim
      for (size_t i = 0; i < section_alpha->GetCDimListSize(); ++i, ++m) {
        // insert data
        ui->table_faults_view->setItem(
            m, 0,
            new QTableWidgetItem(QString::number(
                static_cast<int>(section_alpha->GetCDimElement(i)->value_))));
        ui->table_faults_view->setItem(
            m, 1,
            new QTableWidgetItem(data_model::ResultCode::kResultCodes
                                     [section_alpha->GetCDimElement(i)->value_]
                                         .c_str()));
        ui->table_faults_view->setItem(
            m, 2,
            new QTableWidgetItem(
                section_alpha->GetCDimElement(i)->type_ ==
                        data_model::ResultCode::CodeType::kWarning
                    ? "W"
                    : "E"));
        section_alpha->GetCDimElement(i);
      }
      // edges
      for (size_t i = 0; i < section_alpha->GetEdgeListSize(); ++i, ++m) {
        // insert data
        ui->table_faults_view->setItem(
            m, 0,
            new QTableWidgetItem(QString::number(
                static_cast<int>(section_alpha->GetEdgeElement(i)->value_))));
        ui->table_faults_view->setItem(
            m, 1,
            new QTableWidgetItem(data_model::ResultCode::kResultCodes
                                     [section_alpha->GetEdgeElement(i)->value_]
                                         .c_str()));
        ui->table_faults_view->setItem(
            m, 2,
            new QTableWidgetItem(
                section_alpha->GetEdgeElement(i)->type_ ==
                        data_model::ResultCode::CodeType::kWarning
                    ? "W"
                    : "E"));
        section_alpha->GetEdgeElement(i);
      }
      // defects
      for (size_t i = 0; i < section_alpha->GetDefectListSize(); ++i, ++m) {
        // insert data
        ui->table_faults_view->setItem(
            m, 0,
            new QTableWidgetItem(QString::number(
                static_cast<int>(section_alpha->GetDefectElement(i)->value_))));
        ui->table_faults_view->setItem(
            m, 1,
            new QTableWidgetItem(
                data_model::ResultCode::kResultCodes
                    [section_alpha->GetDefectElement(i)->value_]
                        .c_str()));
        ui->table_faults_view->setItem(
            m, 2,
            new QTableWidgetItem(
                section_alpha->GetDefectElement(i)->type_ ==
                        data_model::ResultCode::CodeType::kWarning
                    ? "W"
                    : "E"));
        section_alpha->GetDefectElement(i);
      }
    } break;
    default:
      // do nothing
      break;
  }
}

void MainWindow::AddQWidgetSectionLabel(QVBoxLayout *layout, int num_elements,
                                        bool apply_stylesheet) {
  QLabel *label = new QLabel(this);
  label->setText(QString::number(num_elements));
  if (apply_stylesheet) {
    label->setStyleSheet(
        (num_elements > 0 ? "background-color:rgb(255, 0, 0); color: 'white'"
                          : "background-color:rgb(0, 255, 0); color: 'white'"));
  }
  label->setFrameShape(QFrame::Shape::Box);
  label->setFrameShadow(QFrame::Shadow::Raised);
  label->setAlignment(Qt::AlignCenter);
  //  label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  label->setFixedSize(20, 20);
  layout->addWidget(label);
}

void MainWindow::AddQWidgetSectionProgressBar(QVBoxLayout *layout,
                                              int endurance, int elasticity) {
  QHBoxLayout *layout_bars = new QHBoxLayout;
  layout_bars->setMargin(0);
  layout_bars->setSpacing(0);

  {  // endurance
    QProgressBar *p_endurance = new QProgressBar(this);
    p_endurance->setOrientation(Qt::Orientation::Vertical);
    //        p_endurance->setStyleSheet("background: #ff7410");
    p_endurance->setRange(0, 100);
    p_endurance->setValue(endurance);
    p_endurance->setFixedSize(10, 66);
    //        p_endurance->setSizePolicy(QSizePolicy::Fixed,
    //        QSizePolicy::Fixed);
    layout_bars->addWidget(p_endurance);
  }
  {  // elasticity
    QProgressBar *p_elasticity = new QProgressBar(this);
    p_elasticity->setOrientation(Qt::Orientation::Vertical);
    //        p_endurance->setStyleSheet("background: #ff7410");
    p_elasticity->setRange(0, 100);
    p_elasticity->setValue(elasticity);
    p_elasticity->setFixedSize(10, 66);
    //        p_endurance->setSizePolicy(QSizePolicy::Fixed,
    //        QSizePolicy::Fixed);
    layout_bars->addWidget(p_elasticity);
  }
  layout->addLayout(layout_bars);
}

void MainWindow::ConnectSignals() {
  // [MODEL -> UI]
  connect(model_, &ModelSections::dataChanged, this,
          &MainWindow::OnDataChanged);
  // [UI -> MODEL]
  connect(this, &MainWindow::NewResult, model_, &ModelSections::OnNewResult);
}

void MainWindow::InitializeLabelPixmap(const std::string &resource_id,
                                       QLabel *label_id) {
  label_id->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
  QPixmap img(resource_id.c_str());
  label_id->setPixmap(
      img.scaled(label_id->width(), label_id->height(), Qt::KeepAspectRatio));
}

void MainWindow::on_button_accept_clicked() { emit NewResult(); }
