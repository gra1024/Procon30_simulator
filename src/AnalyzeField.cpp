#include "AnalyzeField.h"
#include "ui_AnalyzeField.h"

AnalyzeField::AnalyzeField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeField)
{
    ui->setupUi(this);
}

AnalyzeField::~AnalyzeField()
{
    delete ui;
}
