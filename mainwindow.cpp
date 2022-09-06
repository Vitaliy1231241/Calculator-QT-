#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

#define DISPLAY_DIGIT_SCALE_FACTOR 40 + 1

unsigned int MainWindow::buflen = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    hasDecimal = false;

    currentOperator = Operator::NONE;

    setOperatorsEnabled(false);
    // Connect the exit button in the file menu
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));

    ui->statusBar->showMessage("Ready");
    setCentralWidget(ui->centralWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::appendDisplayedNumber(Number number, bool doUpdate) {
    if (++buflen > displayDigitCount) {
        emit ui->numDisplay->overflow();
        return;
    }

    setOperatorsEnabled();

    switch (number) {
    case ZERO:
        inputStringStream << 0;
        break;
    case ONE:
        inputStringStream << 1;
        break;
    case TWO:
        inputStringStream << 2;
        break;
    case THREE:
        inputStringStream << 3;
        break;
    case FOUR:
        inputStringStream << 4;
        break;
    case FIVE:
        inputStringStream << 5;
        break;
    case SIX:
        inputStringStream << 6;
        break;
    case SEVEN:
        inputStringStream << 7;
        break;
    case EIGHT:
        inputStringStream << 8;
        break;
    case NINE:
        inputStringStream << 9;
        break;
    case DECIMAL:
        hasDecimal = true;
        inputStringStream << ".";
        break;
    default:
        throw std::runtime_error("MainWindow::appendDisplayedNumber : Unknown Number value");
    }

    // Set the display
    if (doUpdate) {
        updateResult();
    }
}

void MainWindow::updateResult() {
    ui->numDisplay->display(inputStringStream.str().c_str());
}

void MainWindow::setOperatorsEnabled(bool enable) {
    ui->button_clear->setEnabled(enable);
    ui->button_add->setEnabled(enable);
    ui->button_subtract->setEnabled(enable);
    ui->button_divide->setEnabled(enable);
    ui->button_multiply->setEnabled(enable);
    ui->button_equal->setEnabled(enable);
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);
    displayDigitCount = ui->numDisplay->width() / DISPLAY_DIGIT_SCALE_FACTOR;
    ui->numDisplay->setDigitCount(displayDigitCount);
}

void MainWindow::clearStream(std::string num) {
   inputStringStream.clear();
   inputStringStream.str(num);
   buflen = 0;
   hasDecimal = false;
}

/**
 * @brief Gives a uniform way of invoking any binary operator
 * @param op The operator being triggered
 * @throw Can throw any error depending on the mathematical
 *        operation being performed
 */
void MainWindow::binaryOperatorTriggered(Operator op) {
    if (currentOperator != Operator::NONE) {
        ui->button_equal->click();
        bmh.setLValue(ui->numDisplay->value());
    } else {
        clearStream();
        bmh.setLValue(ui->numDisplay->value());
    }

    hasDecimal = false;
    currentOperator = op;
    setOperatorsEnabled(false);
    ui->button_clear->setEnabled(true);
}

/*--------- SLOTS ----------*/

// Slots for Numerical Button input
void MainWindow::on_button_zero_clicked() {
    if (buflen || bmh.hasLvalue()) {
        appendDisplayedNumber(ZERO, true);
    }
}

void MainWindow::on_button_one_clicked() {
    appendDisplayedNumber(ONE, true);
}

void MainWindow::on_button_two_clicked() {
    appendDisplayedNumber(TWO, true);
}

void MainWindow::on_button_three_clicked() {
    appendDisplayedNumber(THREE, true);
}

void MainWindow::on_button_four_clicked() {
    appendDisplayedNumber(FOUR, true);
}

void MainWindow::on_button_five_clicked() {
    appendDisplayedNumber(FIVE, true);
}

void MainWindow::on_button_six_clicked() {
    appendDisplayedNumber(SIX, true);
}

void MainWindow::on_button_seven_clicked() {
    appendDisplayedNumber(SEVEN, true);
}

void MainWindow::on_button_eight_clicked() {
    appendDisplayedNumber(EIGHT, true);
}

void MainWindow::on_button_nine_clicked() {
    appendDisplayedNumber(NINE, true);
}

void MainWindow::on_button_decimal_clicked() {
    if (!hasDecimal) {
        if (!buflen) {
            appendDisplayedNumber(ZERO);
        }
        appendDisplayedNumber(DECIMAL, true);
    } else {
        QMessageBox::information(this, "Decimal Error", "There can be only one decimal point in a number.");
    }
}

// Slot for  clear button
void MainWindow::on_button_clear_clicked() {
    clearStream("0");
    hasDecimal = false;
    ui->numDisplay->display("0");
    setOperatorsEnabled(false);
    currentOperator = Operator::NONE;
    ui->statusBar->showMessage("Ready");
}

/// Handles display overflow
void MainWindow::on_numDisplay_overflow() {
    const QString ERROR_MESSAGE = "The digit count exceeds the limit of the calculator. The display will be cleared."
                                  "\nTry resizing the window to increase digits handled by the calculator.";

    QMessageBox::information(this, "Overflow", ERROR_MESSAGE);
    ui->button_clear->click();
}

void MainWindow::on_button_add_clicked() {
    binaryOperatorTriggered(Operator::ADD);
    ui->statusBar->showMessage("Operation selected: ADD");
}

void MainWindow::on_button_subtract_clicked() {
    binaryOperatorTriggered(Operator::SUBTRACT);
    ui->statusBar->showMessage("Operation selected: SUBTRACT");
}

void MainWindow::on_button_multiply_clicked() {
    binaryOperatorTriggered(Operator::MULTIPLY);
    ui->statusBar->showMessage("Operation selected: MULTIPLY");
}

 /**
 * @brief performs lvalue / rvalue
 * @throw Can throw a divide by zero error
 */
void MainWindow::on_button_divide_clicked() {
    binaryOperatorTriggered(Operator::DIVIDE);
    ui->statusBar->showMessage("Operation selected: DIVIDE");
}

void MainWindow::on_button_equal_clicked() {
    // Ignore if no lvalue
    if (bmh.hasLvalue()) {
        bmh.setRValue(ui->numDisplay->value());
        try {
            bmh.performOperation(currentOperator);
        } catch (std::runtime_error & e) {
            QMessageBox::critical(this, "Fatal error", e.what());
            ui->button_clear->click();
        }
        clearStream();
        inputStringStream << bmh.getResult();
        bmh.reset();
        updateResult();
        clearStream();
        currentOperator = Operator::NONE;
    }

    ui->statusBar->showMessage("Ready");
}

