#include "calculator.h"
#include <QGridLayout>
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), leftOperand(0.0), waitingForOperand(true)
{
    setWindowTitle("計算機 (Calculator)");
    
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    display->setMinimumHeight(50);
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(display, 0, 0, 1, 4);
    
    // Create digit buttons (0-9)
    for (int i = 0; i < 10; ++i) {
        QString text = QString::number(i);
        QPushButton *button = createButton(text, SLOT(digitClicked()));
        
        if (i == 0) {
            mainLayout->addWidget(button, 4, 0, 1, 2);
        } else {
            int row = 3 - (i - 1) / 3;
            int col = (i - 1) % 3;
            mainLayout->addWidget(button, row, col);
        }
    }
    
    // Create operator buttons
    QPushButton *addButton = createButton("+", SLOT(operatorClicked()));
    QPushButton *subtractButton = createButton("-", SLOT(operatorClicked()));
    QPushButton *multiplyButton = createButton("×", SLOT(operatorClicked()));
    QPushButton *divideButton = createButton("÷", SLOT(operatorClicked()));
    
    mainLayout->addWidget(divideButton, 1, 3);
    mainLayout->addWidget(multiplyButton, 2, 3);
    mainLayout->addWidget(subtractButton, 3, 3);
    mainLayout->addWidget(addButton, 4, 3);
    
    // Create other function buttons
    QPushButton *pointButton = createButton(".", SLOT(pointClicked()));
    QPushButton *equalButton = createButton("=", SLOT(equalClicked()));
    QPushButton *clearButton = createButton("C", SLOT(clearClicked()));
    QPushButton *clearAllButton = createButton("AC", SLOT(clearAllClicked()));
    
    mainLayout->addWidget(clearAllButton, 1, 0);
    mainLayout->addWidget(clearButton, 1, 1);
    mainLayout->addWidget(pointButton, 4, 2);
    mainLayout->addWidget(equalButton, 1, 2);
    
    setLayout(mainLayout);
    
    // Set minimum size
    setMinimumSize(300, 400);
}

Calculator::~Calculator()
{
}

QPushButton *Calculator::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->setMinimumSize(60, 60);
    
    QFont font = button->font();
    font.setPointSize(font.pointSize() + 4);
    button->setFont(font);
    
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void Calculator::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString digitValue = clickedButton->text();
    
    if (display->text() == "0" && digitValue == "0")
        return;
    
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    
    display->setText(display->text() + digitValue);
}

void Calculator::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString clickedOperator = clickedButton->text();
    
    double operand = display->text().toDouble();
    
    if (!currentOperator.isEmpty()) {
        if (waitingForOperand) {
            // Just change the operator
            currentOperator = clickedOperator;
            return;
        }
        calculate();
    } else {
        leftOperand = operand;
    }
    
    currentOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    if (!currentOperator.isEmpty()) {
        calculate();
        currentOperator.clear();
        waitingForOperand = true;
    }
}

void Calculator::clearClicked()
{
    if (waitingForOperand)
        return;
    
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearAllClicked()
{
    leftOperand = 0.0;
    currentOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    
    if (!display->text().contains("."))
        display->setText(display->text() + ".");
    
    waitingForOperand = false;
}

void Calculator::calculate()
{
    double rightOperand = display->text().toDouble();
    double result = 0.0;
    
    if (currentOperator == "+") {
        result = leftOperand + rightOperand;
    } else if (currentOperator == "-") {
        result = leftOperand - rightOperand;
    } else if (currentOperator == "×") {
        result = leftOperand * rightOperand;
    } else if (currentOperator == "÷") {
        if (rightOperand == 0.0) {
            display->setText("Error");
            leftOperand = 0.0;
            currentOperator.clear();
            waitingForOperand = true;
            return;
        }
        result = leftOperand / rightOperand;
    }
    
    // Format the result to remove unnecessary trailing zeros
    QString resultStr = QString::number(result, 'g', 10);
    display->setText(resultStr);
    leftOperand = result;
}
