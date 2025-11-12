#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();
    void operatorClicked();
    void equalClicked();
    void clearClicked();
    void clearAllClicked();
    void pointClicked();

private:
    QPushButton *createButton(const QString &text, const char *member);
    void calculate();
    bool hasOperator() const;

    QLineEdit *display;
    
    double leftOperand;
    QString currentOperator;
    bool waitingForOperand;
};

#endif // CALCULATOR_H
