#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
    }

private slots:
    void buttonClicked() {
        QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
        if (!clickedButton) return;

        QString buttonText = clickedButton->text();
        if (buttonText == "C") {
            displayLineEdit->clear();
        } else if (buttonText == "=") {
            QString expression = displayLineEdit->text();
            displayLineEdit->setText(QString::number(evalExpression(expression)));
        } else {
            displayLineEdit->insert(buttonText);
        }
    }

private:
    void setupUI() {
        QGridLayout *gridLayout = new QGridLayout(this);
        displayLineEdit = new QLineEdit(this);
        displayLineEdit->setAlignment(Qt::AlignRight);
        displayLineEdit->setReadOnly(true);
        gridLayout->addWidget(displayLineEdit, 0, 0, 1, 4);

        const char *buttons[4][4] = {
            {"7", "8", "9", "/"},
            {"4", "5", "6", "*"},
            {"1", "2", "3", "-"},
            {"0", "C", "=", "+"}
        };

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                QPushButton *button = new QPushButton(buttons[i][j], this);
                connect(button, &QPushButton::clicked, this, &Calculator::buttonClicked);
                gridLayout->addWidget(button, i + 1, j);
            }
        }

        setLayout(gridLayout);
    }

    double evalExpression(const QString &expression) {
        // Implement a simple expression evaluator
        // You can use a more sophisticated expression evaluation library if needed
        return QLocale().toDouble(expression);
    }

    QLineEdit *displayLineEdit;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Calculator calculator;
    calculator.setWindowTitle("Simple Calculator");
    calculator.setGeometry(100, 100, 300, 400);
    calculator.show();

    return app.exec();
}

#include "main.moc"
