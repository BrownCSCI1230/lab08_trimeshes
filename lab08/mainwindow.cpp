#include "mainwindow.h"
#include "Settings.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QGroupBox>

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
     *       |
     *     p1Layout, p2Layout
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
    triangleCB = new QRadioButton(sidebar); // Triangle button
    triangleCB->setText(QStringLiteral("Triangle"));
    triangleCB->setChecked(true); // Default Triangle toggled
    cubeCB = new QRadioButton(sidebar); // Cube button
    cubeCB->setText(QStringLiteral("Cube"));
    sphereCB = new QRadioButton(sidebar); // Sphere button
    sphereCB->setText(QStringLiteral("Sphere"));

    // Creates the boxes containing the parameter sliders and number boxes
    QGroupBox *p1Layout = new QGroupBox(); // horizonal slider 1 alignment
    QHBoxLayout *l1 = new QHBoxLayout();
    QGroupBox *p2Layout = new QGroupBox(); // horizonal slider 2 alignment
    QHBoxLayout *l2 = new QHBoxLayout();

    // Create slider controls to control parameters
    p1Slider = new QSlider(Qt::Orientation::Horizontal, sidebar); // Parameter 1 slider
    p1Slider->setTickInterval(1);
    p1Slider->setMinimum(0); // TODO: Maybe change the minimum depending if Cube or Sphere is selected
    p1Slider->setMaximum(50);

    p1Box = new QSpinBox();
    p1Box->setMinimum(0);
    p1Box->setMaximum(50);
    p1Box->setSingleStep(1);

    p2Slider = new QSlider(Qt::Orientation::Horizontal, sidebar); // Parameter 2 slider
    p2Slider->setTickInterval(1);
    p2Slider->setMinimum(0); // TODO: Maybe change the minimum depending if Cube or Sphere is selected
    p2Slider->setMaximum(50);

    p2Box = new QSpinBox();
    p2Box->setMinimum(0);
    p2Box->setMaximum(50);
    p2Box->setSingleStep(1);

    // Adds the slider and number box to the parameter layouts
    l1->addWidget(p1Slider);
    l1->addWidget(p1Box);
    p1Layout->setLayout(l1);

    l2->addWidget(p2Slider);
    l2->addWidget(p2Box);
    p2Layout->setLayout(l2);

    // Add the labels and checkbox widgets to vLayout for vertical alignment (order matters!)
    vLayout->addWidget(trimesh_label);
    vLayout->addWidget(triangleCB);
    vLayout->addWidget(cubeCB);
    vLayout->addWidget(sphereCB);
    vLayout->addWidget(width_spacer);
    vLayout->addWidget(params_label);
    vLayout->addWidget(param1_label);
    vLayout->addWidget(p1Layout);
    vLayout->addWidget(param2_label);
    vLayout->addWidget(p2Layout);

    // Connects the sliders and number boxes for the parameters
    connectParam1();
    connectParam2();

    connectTriangle();
    connectCube();
    connectSphere();
}

//******************************** Handles Parameter 1 UI Changes ********************************//
void MainWindow::connectParam1()
{
    connect(p1Slider, &QSlider::valueChanged, this, &MainWindow::onValChangeP1);
    connect(p1Box, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::onValChangeP1);
}

void MainWindow::disconnectParam1()
{
    disconnect(p1Slider, &QSlider::valueChanged, this, &MainWindow::onValChangeP1);
    disconnect(p1Box, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::onValChangeP1);
}

void MainWindow::onValChangeP1(int newValue)
{
    disconnectParam1();
    p1Slider->setValue(newValue);
    p1Box->setValue(newValue);
    settings.shapeParameter1 = p1Slider->value();
    connectParam1();
}

//******************************** Handles Parameter 2 UI Changes ********************************//
void MainWindow::connectParam2()
{
    connect(p2Slider, &QSlider::valueChanged, this, &MainWindow::onValChangeP2);
    connect(p2Box, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::onValChangeP2);
}

void MainWindow::disconnectParam2()
{
    disconnect(p2Slider, &QSlider::valueChanged, this, &MainWindow::onValChangeP2);
    disconnect(p2Box, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::onValChangeP2);
}

void MainWindow::onValChangeP2(int newValue)
{
    disconnectParam2();
    p2Slider->setValue(newValue);
    p2Box->setValue(newValue);
    settings.shapeParameter2 = p2Slider->value();
    connectParam2();
}

//******************************** Handles Shape Type UI Changes ********************************//

// triangle
void MainWindow::connectTriangle()
{
    connect(triangleCB, &QRadioButton::clicked, this, &MainWindow::onTriChange);
}

void MainWindow::disconnectTriangle()
{
    disconnect(triangleCB, &QRadioButton::clicked, this, &MainWindow::onTriChange);
}

void MainWindow::onTriChange()
{
    disconnectTriangle();
    settings.shapeType = SHAPE_TRIANGLE;
    connectTriangle();
}

// cube
void MainWindow::connectCube()
{
    connect(cubeCB, &QRadioButton::clicked, this, &MainWindow::onCubeChange);
}

void MainWindow::disconnectCube()
{
    disconnect(cubeCB, &QRadioButton::clicked, this, &MainWindow::onCubeChange);
}

void MainWindow::onCubeChange()
{
    disconnectCube();
    settings.shapeType = SHAPE_CUBE;
    connectCube();
}

// sphere
void MainWindow::connectSphere()
{
    connect(sphereCB, &QRadioButton::clicked, this, &MainWindow::onSphereChange);
}

void MainWindow::disconnectSphere()
{
    disconnect(sphereCB, &QRadioButton::clicked, this, &MainWindow::onSphereChange);
}

void MainWindow::onSphereChange()
{
    disconnectSphere();
    settings.shapeType = SHAPE_SPHERE;
    connectSphere();
}


MainWindow::~MainWindow()
{
}

