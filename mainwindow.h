#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sstream>

#include <QMainWindow>
#include <QLabel>

#include "binarymathhelper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_zero_clicked();

    void on_button_one_clicked();

    void on_button_two_clicked();

    void on_button_three_clicked();

    void on_button_four_clicked();

    void on_button_five_clicked();

    void on_button_six_clicked();

    void on_button_seven_clicked();

    void on_button_eight_clicked();

    void on_button_nine_clicked();

    void on_button_decimal_clicked();

    void on_button_clear_clicked();

    void on_numDisplay_overflow();

    void on_button_add_clicked();

    void on_button_subtract_clicked();

    void on_button_multiply_clicked();

    void on_button_divide_clicked();

    void on_button_equal_clicked();

    private:
    enum Number {
        ZERO,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        DECIMAL
    };

    bool hasDecimal;

    static unsigned int buflen;
    std::stringstream inputStringStream;

    unsigned int displayDigitCount;

    Ui::MainWindow *ui;

    void appendDisplayedNumber(Number number, bool doUpdate = false);
    void updateResult();
    void setOperatorsEnabled(bool enable = true);
    void resizeEvent(QResizeEvent *event);

    BinaryMathHelper bmh;
    Operator currentOperator;

    void clearStream(std::string num = std::string());

    void binaryOperatorTriggered(Operator op);
};

#endif // MAINWINDOW_H
