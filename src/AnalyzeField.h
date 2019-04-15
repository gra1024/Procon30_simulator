#ifndef ANALYZEFIELD_H
#define ANALYZEFIELD_H

#include <QWidget>

namespace Ui {
class AnalyzeField;
}

class AnalyzeField : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyzeField(QWidget *parent = nullptr);
    ~AnalyzeField();

private:
    Ui::AnalyzeField *ui;
};

#endif // ANALYZEFIELD_H
