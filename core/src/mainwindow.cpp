#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>
#include <QHBoxLayout>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 主布局：水平布局
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 左侧按钮栏
    sidebarWidget = new QWidget();
    sidebarWidget->setFixedWidth(60);                                     // 固定宽度，类似 VSCode
    sidebarWidget->setStyleSheet("QWidget { background-color: #2C2C2C; }" // 深色背景
    );

    sidebarLayout = new QVBoxLayout(sidebarWidget);
    sidebarLayout->setContentsMargins(5, 5, 5, 5);
    sidebarLayout->setSpacing(2);
    sidebarLayout->addStretch(); // 底部弹簧，按钮靠上对齐

    // 右侧内容区域
    contentStack = new QStackedWidget();
    contentStack->setStyleSheet("QStackedWidget { background-color: #1E1E1E; }" // 深色背景
    );

    // 添加到主布局
    mainLayout->addWidget(sidebarWidget);
    mainLayout->addWidget(contentStack, 1); // 内容区域占据剩余空间

    // 按钮组管理（互斥选择）
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);
    connect(buttonGroup,
            QOverload<int>::of(&QButtonGroup::idClicked),
            this,
            &MainWindow::onSidebarButtonClicked);

    resize(1000, 700);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPluginManager(PluginManager *manager)
{
    m_pluginManager = manager;
    
    if (m_pluginManager) {
        connect(m_pluginManager, &PluginManager::pluginLoaded,
                this, &MainWindow::onPluginLoaded);
        connect(m_pluginManager, &PluginManager::pluginUnloaded,
                this, &MainWindow::onPluginUnloaded);
    }
}

void MainWindow::onPluginLoaded(IPlugin *plugin)
{
    if (!plugin)
        return;

    QString logMsg = QString("插件已加载: %1 (版本: %2)").arg(plugin->name()).arg(plugin->version());

    QWidget *pluginWidget = plugin->createWidget();

    int stackIndex = contentStack->addWidget(pluginWidget);

    addPluginToSidebar(plugin);
}

void MainWindow::onPluginUnloaded(const QString &pluginName) {}

void MainWindow::onPluginSelected(QListWidgetItem *item) {}

void MainWindow::onSidebarButtonClicked(int id)
{
    if (!pluginMap.contains(id)) {
        return;
    }

    // 切换到对应的界面
    // buttonId 和 stackIndex 是对应的（按加载顺序）
    contentStack->setCurrentIndex(id);

    qDebug() << "Switched to plugin:" << pluginMap[id]->name();
}

void MainWindow::addPluginToSidebar(IPlugin *plugin)
{
    // 创建侧边栏按钮
    QToolButton *button = new QToolButton();
    button->setIcon(plugin->icon());
    button->setToolTip(plugin->displayName());
    button->setCheckable(true);
    button->setAutoRaise(true);
    button->setIconSize(QSize(32, 32));
    button->setFixedSize(50, 50);

    // 按钮样式
    button->setStyleSheet("QToolButton {"
                          "    border: none;"
                          "    border-radius: 4px;"
                          "    padding: 8px;"
                          "}"
                          "QToolButton:hover {"
                          "    background-color: #3E3E3E;"
                          "}"
                          "QToolButton:checked {"
                          "    background-color: #094771;"
                          "}");

    // 分配唯一 ID
    int buttonId = nextButtonId++;
    buttonGroup->addButton(button, buttonId);

    // 保存映射关系
    pluginMap.insert(buttonId, plugin);

    // 插入到布局中（stretch 之前）
    sidebarLayout->insertWidget(sidebarLayout->count() - 1, button);
}
