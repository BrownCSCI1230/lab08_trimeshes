#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QRadioButton>
#include <QSlider>

MainWindow::MainWindow()
{
    // Create glWidget for OpenGL stuff
    glWidget = new GLWidget;

    // Create QWidget for sidebar toggle stuff
    QWidget *sidebar = new QWidget;

    /* Set up the layouts (parent-child diagram):
     *
     *                 hLayout
     *                 /     \
     *          vLayout       glWidget (canvas)
     *             |
     *        sidebar (toolbar)
     *            |
     *     labels,sliders,buttons,...
     *
     */
    QHBoxLayout *hLayout = new QHBoxLayout(); // horizontal alignment
    QVBoxLayout *vLayout = new QVBoxLayout(); // vertical alignment
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->addWidget(sidebar);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(glWidget, 1);
    this->setLayout(hLayout);

    // Create labels in sidebox
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    QLabel *trimesh_label = new QLabel(sidebar); // Trimeshes label
    trimesh_label->setText("Trimeshes");
    trimesh_label->setFont(font);
    QLabel *params_label = new QLabel(sidebar); // Parameters label
    params_label->setText("Parameters");
    params_label->setFont(font);
    QLabel *param1_label = new QLabel(sidebar); // Parameter 1 label
    param1_label->setText("Parameter 1:");
    QLabel *param2_label = new QLabel(sidebar); // Parameter 2 label
    param2_label->setText("Parameter 2:");
    QLabel *width_spacer = new QLabel(sidebar); // cheat-y way of adding more width to the QVBoxLayout
    width_spacer->setText("                                               ");
    width_spacer->setFont(font);

    // Create checkbox controls to toggle Cube and Sphere
    QRadioButton *triangleCB = new QRadioButton(sidebar); // Triangle button
    triangleCB->setText(QStringLiteral("Triangle"));
    triangleCB->setChecked(true); // Default Triangle toggled
    QRadioButton *cubeCB = new QRadioButton(sidebar); // Cube button
    cubeCB->setText(QStringLiteral("Cube"));
    QRadioButton *sphereCB = new QRadioButton(sidebar); // Sphere button
    sphereCB->setText(QStringLiteral("Sphere"));

    // Create slider controls to control parameters
    QSlider *param1 = new QSlider(Qt::Orientation::Horizontal, sidebar); // Parameter 1 slider
    param1->setTickInterval(1);
    param1->setMinimum(0); // TODO: Maybe change the minimum depending if Cube or Sphere is selected
    param1->setMaximum(50);
    QSlider *param2 = new QSlider(Qt::Orientation::Horizontal, sidebar); // Parameter 2 slider
    param1->setTickInterval(1);
    param1->setMinimum(0); // TODO: Maybe change the minimum depending if Cube or Sphere is selected
    param1->setMaximum(50);

    // Add the labels and checkbox widgets to vLayout for vertical alignment (order matters!)
    vLayout->addWidget(trimesh_label);
    vLayout->addWidget(triangleCB);
    vLayout->addWidget(cubeCB);
    vLayout->addWidget(sphereCB);
    vLayout->addWidget(width_spacer);
    vLayout->addWidget(params_label);
    vLayout->addWidget(param1_label);
    vLayout->addWidget(param1);
    vLayout->addWidget(param2_label);
    vLayout->addWidget(param2);

}

MainWindow::~MainWindow()
{
}

