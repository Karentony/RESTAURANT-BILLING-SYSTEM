#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

class RestaurantBillingWindow : public QWidget {
public:
    RestaurantBillingWindow(QWidget *parent = nullptr);

private slots:
    void viewMenu();
    void placeOrder();

private:
    QLabel *label;
};

RestaurantBillingWindow::RestaurantBillingWindow(QWidget *parent)
    : QWidget(parent), label(new QLabel(this)) {

    // Set window title and layout
    setWindowTitle("Restaurant Billing System");
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add label to show status
    label->setText("Welcome to the Restaurant Billing System");
    layout->addWidget(label);

    // Create View Menu button
    QPushButton *viewMenuButton = new QPushButton("View Available Menu", this);
    layout->addWidget(viewMenuButton);
    connect(viewMenuButton, &QPushButton::clicked, this, &RestaurantBillingWindow::viewMenu);

    // Create Place Order button
    QPushButton *placeOrderButton = new QPushButton("Place an Order", this);
    layout->addWidget(placeOrderButton);
    connect(placeOrderButton, &QPushButton::clicked, this, &RestaurantBillingWindow::placeOrder);

    // Create Exit button
    QPushButton *exitButton = new QPushButton("Exit", this);
    layout->addWidget(exitButton);
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    // Set the layout
    setLayout(layout);
}

void RestaurantBillingWindow::viewMenu() {
    QMessageBox::information(this, "Available Menu", 
        "1. Burger - $8.99\n"
        "2. Pizza - $12.49\n"
        "3. Pasta - $10.99\n"
        "4. Salad - $6.49\n"
        "5. Soda - $1.99");
}

void RestaurantBillingWindow::placeOrder() {
    QMessageBox::information(this, "Place Order", 
        "You can now place your order.\nPlease proceed with selecting menu items.");
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RestaurantBillingWindow window;
    window.show();

    return app.exec();
}
