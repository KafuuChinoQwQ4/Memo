#include "logincontrolwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QAction>
#include <QMenu>

LoginControlWidget::LoginControlWidget(QWidget *parent)
    : QWidget{parent},
      m_optionsMenu(nullptr) // 初始化菜单指针为空
{
    // --- 同意协议区域 ---
    QHBoxLayout *agreementLayout = new QHBoxLayout();
    agreementLayout->setSpacing(0); // 控件间的间距由标签的边距处理

    m_agreementCheckBox = new QCheckBox(this); // 创建“同意协议”的复选框
    m_agreementCheckBox->setCursor(Qt::PointingHandCursor); // 设置鼠标悬停样式为手形

    QLabel *agreementLabel = new QLabel(this);
    // 使用富文本格式来设置不同部分的样式，而样式表用于设置整个控件的盒子模型
    // agreementLabel->setStyleSheet("margin-left: 2px;"); // 设置标签左边距
    // 设置文本内容，包含可点击的链接。R"(...)" 是C++11的原始字符串字面量，方便书写包含特殊字符的字符串
    agreementLabel->setText(R"(<span style="font-size:12px; color:gray;">已阅读并同意 </span><a href="#" style="font-size:12px; color:blue; text-decoration:none;">服务协议</a><span style="font-size:12px; color:gray;"> 和 </span><a href="#" style="font-size:12px; color:blue; text-decoration:none;">隐私保护指引</a>)");
    agreementLabel->setTextFormat(Qt::RichText); // 声明文本为富文本格式
    agreementLabel->setOpenExternalLinks(true); // 允许Qt自动处理并打开链接（例如在浏览器中）

    agreementLayout->addWidget(m_agreementCheckBox);
    agreementLayout->addWidget(agreementLabel);
    agreementLayout->addStretch(); // 添加弹性空间，使布局靠左

    // --- 登录按钮 ---
    m_loginButton = new QPushButton(tr("登录"), this);
    m_loginButton->setObjectName("loginButton"); // 设置对象名，用于QSS样式
    m_loginButton->setCursor(Qt::PointingHandCursor);
    m_loginButton->setEnabled(false); // 默认禁用登录按钮，直到用户同意协议

    // --- 信号与槽连接 ---
    // 复选框状态改变时，触发 onAgreementCheckBoxStateChanged 槽函数
    connect(m_agreementCheckBox, &QCheckBox::stateChanged, this, &LoginControlWidget::onAgreementCheckBoxStateChanged);
    // 登录按钮点击时，发射 loginButtonClicked 信号
    connect(m_loginButton, &QPushButton::clicked, this, &LoginControlWidget::loginButtonClicked);

    // --- 更多选项区域 ---
    QHBoxLayout *optionsLayout = new QHBoxLayout();
    optionsLayout->setSpacing(8); // 设置选项之间的间距

    const QString optionLabelStyle = "QLabel { color: #0078D7; font-size: 12px; }"; // 统一定义选项标签的样式

    QLabel *scanCodeLabel = new QLabel(tr("扫码登录"), this);
    scanCodeLabel->setStyleSheet(optionLabelStyle);
    scanCodeLabel->setCursor(Qt::PointingHandCursor);
    // 为了让QLabel能响应点击，需要更复杂的事件处理，这里暂时只设置了样式
    // connect(scanCodeLabel, &QLabel::linkActivated, this, &LoginControlWidget::scanCodeClicked);

    QLabel *separatorLabel = new QLabel("|", this);
    separatorLabel->setStyleSheet("QLabel { color: #D3D3D3; }"); // 分隔符样式

    m_moreOptionsButton = new QPushButton(tr("更多选项"), this);
    // 为“更多选项”按钮设置详细的样式，使其看起来像一个标签链接
    m_moreOptionsButton->setStyleSheet("QPushButton { color: #0078D7; font-size: 12px; border: none; background: transparent; padding: 2px; }"
                                       "QPushButton:hover { background-color: #E0E0E0; border-radius: 2px; }");
    m_moreOptionsButton->setCursor(Qt::PointingHandCursor);
    // 点击“更多选项”按钮时，显示一个菜单
    connect(m_moreOptionsButton, &QPushButton::clicked, this, &LoginControlWidget::onMoreOptionsButtonClicked);

    optionsLayout->addStretch(); // 添加弹性空间
    optionsLayout->addWidget(scanCodeLabel);
    optionsLayout->addWidget(separatorLabel);
    optionsLayout->addWidget(m_moreOptionsButton);
    optionsLayout->addStretch(); // 再次添加弹性空间，实现居中效果

    // --- 主布局 ---
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(agreementLayout); // 添加协议区域布局
    mainLayout->addSpacing(10); // 添加垂直间距
    mainLayout->addWidget(m_loginButton); // 添加登录按钮
    mainLayout->addSpacing(15); // 添加垂直间距
    mainLayout->addLayout(optionsLayout); // 添加更多选项布局
    mainLayout->setContentsMargins(0, 0, 0, 0); // 控件本身无外边距
}

// 公有方法，用于从外部控制登录按钮的可用状态
void LoginControlWidget::setLoginButtonEnabled(bool enable)
{
    m_loginButton->setEnabled(enable);
}

// “同意协议”复选框状态改变时调用的槽函数
void LoginControlWidget::onAgreementCheckBoxStateChanged(int state)
{
    // 发射信号，将复选框的选中状态（布尔值）传递出去，以便其他部分（如主窗口）可以响应
    emit agreementToggled(state == Qt::Checked);
}

// “更多选项”按钮点击时调用的槽函数
void LoginControlWidget::onMoreOptionsButtonClicked()
{
    // 使用延迟加载（懒汉模式）创建菜单，只有在第一次点击时才创建，以优化性能
    if (!m_optionsMenu) {
        m_optionsMenu = new QMenu(this);
        m_optionsMenu->addAction(tr("忘记密码"));
        m_optionsMenu->addSeparator(); // 添加分隔线
        QAction *registerAction = m_optionsMenu->addAction(tr("注册账号"));
        connect(registerAction, &QAction::triggered, this, &LoginControlWidget::registerAccountClicked);
        // 为菜单设置自定义QSS样式
        m_optionsMenu->setStyleSheet(
            "QMenu {"
            "  background-color: #FCFCFC;"
            "  border: 1px solid #E0E0E0;"
            "  border-radius: 8px;"
            "  padding: 5px;"
            "}"
            "QMenu::item {"
            "  font-size: 13px;"
            "  color: #333333;"
            "  padding: 10px 25px;"
            "  border-radius: 4px;"
            "  margin: 0px 5px;"
            "}"
            "QMenu::item:selected {"
            "  background-color: #F0F0F0;"
            "  color: #0078D7;"
            "}"
            "QMenu::separator {"
            "  height: 1px;"
            "  background: #E5E5E5;"
            "  margin-left: 10px;"
            "  margin-right: 10px;"
            "}"
            );
    }
    // 在“更多选项”按钮的左下角位置弹出菜单
    m_optionsMenu->popup(m_moreOptionsButton->mapToGlobal(QPoint(0, m_moreOptionsButton->height())));
    // 发射信号，通知其他部分“更多选项”被点击了
    emit moreOptionsClicked();
}
