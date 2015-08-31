#include "AdsFrame.h"

// Input bit-flags
#define KEY_BACK 1

const static unsigned int g_formsCount = 2;
const static unsigned int g_imgsCount = 4;

CAdsFrame game;

CAdsFrame::CAdsFrame()
    : m_scene(NULL), m_formNode(NULL), m_formNodeParent(NULL), m_formSetting(NULL), m_activeForm(NULL), m_imgPreIndex(0), m_bImgAnimation(false), m_hRatio(1.0f)
{
    const char* formFiles[] = 
    {
        "res/form/formBind.form",
        "res/form/formTopup.form",
    };
    const char* imgFiles[] =
    {
        "res/jpg/img001.jpg",
        "res/jpg/img002.jpg",
        "res/jpg/img003.jpg",
        "res/jpg/img004.jpg",
    };

    m_formFiles.assign(formFiles, formFiles + g_formsCount);
    m_imgFiles.assign(imgFiles, imgFiles + g_imgsCount);
}

void CAdsFrame::finalize()
{
    SAFE_RELEASE(m_scene);
    SAFE_RELEASE(m_formNode);
    SAFE_RELEASE(m_formSetting);
    for (unsigned int i = 0; i < m_forms.size(); i++)
    {
        SAFE_RELEASE(m_forms[i]);
    }
    for (unsigned int i = 0; i < m_sBatchs.size(); i++)
    {
        SAFE_DELETE(m_sBatchs[i]);
    }
    //SAFE_RELEASE(m_font);
}

void CAdsFrame::drawSplash(void* param)
{
    clear(CLEAR_COLOR_DEPTH, Vector4(0, 0, 0, 1), 1.0f, 0);
    SpriteBatch* batch = SpriteBatch::create("res/png/logo_powered_white.png");
    batch->start();
    batch->draw(this->getWidth() * 0.5f, this->getHeight() * 0.5f, 0.0f, 512.0f, 512.0f, 0.0f, 1.0f, 1.0f, 0.0f, Vector4::one(), true);
    batch->finish();
    SAFE_DELETE(batch);
}

void CAdsFrame::initialize()
{
    // Display the gameplay splash screen for at least 1 second.
    displayScreen(this, &CAdsFrame::drawSplash, NULL, 1000L);

    setMultiTouch(true);
    setVsync(false);

    //m_font = Font::create("/res/font/msyh.gpb");

    m_formSetting = Form::create("res/form/formSetting.form");
    m_formSetting->setFocus();

    RadioButton* form0Button = static_cast<RadioButton*>(m_formSetting->getControl("rdoBind"));
    form0Button->addListener(this, Control::Listener::CLICK);

    RadioButton* form1Button = static_cast<RadioButton*>(m_formSetting->getControl("rdoTopup"));
    form1Button->addListener(this, Control::Listener::CLICK);

    RadioButton* form2Button = static_cast<RadioButton*>(m_formSetting->getControl("rdoProgram"));
    form2Button->addListener(this, Control::Listener::CLICK);

    RadioButton* img1Button = static_cast<RadioButton*>(m_formSetting->getControl("rdoImg1"));
    img1Button->addListener(this, Control::Listener::CLICK);

    RadioButton* img2Button = static_cast<RadioButton*>(m_formSetting->getControl("rdoImg2"));
    img2Button->addListener(this, Control::Listener::CLICK);

    RadioButton* img3Button = static_cast<RadioButton*>(m_formSetting->getControl("rdoImg3"));
    img3Button->addListener(this, Control::Listener::CLICK);

    RadioButton* img4Button = static_cast<RadioButton*>(m_formSetting->getControl("rdoImg4"));
    img4Button->addListener(this, Control::Listener::CLICK);
    for (unsigned int i = 0; i < m_formFiles.size(); i++)
    {
        GP_INFO("Begin to create form [%d]...", i);
		Form* form = Form::create(m_formFiles[i]);
        form->setEnabled(false);
        m_forms.push_back(form);
    }
    m_formIndex = 0;
    for (unsigned int i = 0; i < m_imgFiles.size(); i++)
    {
        GP_INFO("Begin to create form [%d]...", i);
        SpriteBatch* batch = SpriteBatch::create(m_imgFiles[i]);
        m_sBatchs.push_back(batch);
    }
    m_imgIndex = 0;

    // Create a form programmatically.
    createSampleForm();

    Button* button = static_cast<Button*>(m_forms[0]->getControl("yesButton"));
    button->setFocus();

    // Create a scene with a camera node.
    Camera* camera = Camera::createPerspective(45.0f, (float)getWidth() / (float)getHeight(), 0.25f, 100.0f);
    m_scene = Scene::create();
    Node* cameraNode = m_scene->addNode("Camera");
    cameraNode->setCamera(camera);
    m_scene->setActiveCamera(camera);
    SAFE_RELEASE(camera);
    m_formNodeParent = m_scene->addNode("FormParent");
    m_formNode = Node::create("Form");
    m_formNodeParent->addChild(m_formNode);
    
    formChanged();
    imgChanged();
}

void CAdsFrame::formChanged()
{
    if (m_activeForm)
    {
        m_activeForm->setEnabled(false);
    }
    m_activeForm = m_forms[m_formIndex];
    m_activeForm->setEnabled(true);
    m_activeForm->setFocus();
    //m_activeForm->setAlignment(Control::ALIGN_BOTTOM_HCENTER);//ALIGN_VCENTER_HCENTER);

    // Add the form to a node to allow it to be placed in 3D space.
    const Rectangle& bounds = m_activeForm->getBounds();
    float scale;
    if (bounds.width >= bounds.height)
    {
        scale = 1.0f / bounds.width;
    }
    else
    {
        scale = 1.0f / bounds.height;
    }

    ///< 还不知道控制什么
    m_formNode->setScale(scale, scale, 1.0f);

    ///< 图片缩放比例
    m_formNodeParent->setTranslation(0, 0, -1.5f);

    ///< 有待观察控制内容
    m_formNode->setTranslation(-0.5f, -0.5f, 0);
    m_formNode->setDrawable(m_activeForm);
}

void CAdsFrame::imgChanged()
{
    clear(CLEAR_COLOR_DEPTH, Vector4(0, 0, 0, 1), 1.0f, 0);
    if (m_bImgAnimation)
    {
        m_sBatchs[m_imgPreIndex]->start();
        m_sBatchs[m_imgPreIndex]->draw(this->getWidth() * m_hRatio, this->getHeight() * 0.0f, 0.0f, this->getWidth() * (1.0f - m_hRatio), this->getHeight() * 1.0f, 0.0f, 1.0f, (1.0f - m_hRatio), 0.0f, Vector4::one(), false);
        m_sBatchs[m_imgPreIndex]->finish();
    }
    m_sBatchs[m_imgIndex]->start();
    m_sBatchs[m_imgIndex]->draw(this->getWidth() * 0.0f, this->getHeight() * 0.0f, 0.0f, this->getWidth() * m_hRatio, this->getHeight() * 1.0f, (1.0f - m_hRatio), 1.0f, 1.0f, 0.0f, Vector4::one(), false);
    m_sBatchs[m_imgIndex]->finish();
}

void CAdsFrame::createSampleForm()
{
    Form* form = Form::create("testForm", NULL);
    form->setSize(600, 600);

    Label* label = Label::create("testLabel");
    label->setPosition(50, 50);
    label->setSize(200, 50);
    label->setText("Hello");
    form->addControl(label);
    label->release();

    Button* button = Button::create("opacityButton");
    button->setPosition(45, 100);
    button->setSize(200, 100);
    button->setText("This is a button.  Click to change its opacity.");
    button->addListener(this, Control::Listener::CLICK);
    form->addControl(button);
    button->release();

    //GP_WARN("Before create image control...");
    //ImageControl* pImgCtl = ImageControl::create("testImg");
    //pImgCtl->setPosition(50, 200);
    //pImgCtl->setSize(200, 200);
    //pImgCtl->setImage("res/hello.jpg");//logo.png");//
    //form->addControl(pImgCtl);
    //pImgCtl->release();

    //pImgCtl = ImageControl::create("testImg2");
    //pImgCtl->setPosition(260, 200);
    //pImgCtl->setSize(200, 200);
    //pImgCtl->setImage("res/hello_jpg.png");//test.jpg");//
    //form->addControl(pImgCtl);
    //pImgCtl->release();

    //pImgCtl = ImageControl::create("testImg3");
    //pImgCtl->setPosition(50, 405);
    //pImgCtl->setSize(200, 113);
    //pImgCtl->setImage("res/test.jpg");//test-1.png");//
    //pImgCtl->setRegionSrc(0, 0, 200, 113);
    //form->addControl(pImgCtl);
    //pImgCtl->release();

    //pImgCtl = ImageControl::create("testImg4");
    //pImgCtl->setPosition(260, 405);
    //pImgCtl->setSize(200, 200);
    //pImgCtl->setImage("res/logo.png");//test.jpg");//
    //form->addControl(pImgCtl);
    //pImgCtl->release();
    //GP_WARN("End create image control...");

    form->setEnabled(false);
    m_forms.push_back(form);
}

void CAdsFrame::update(float elapsedTime)
{
    // float speedFactor = 0.001f * elapsedTime;

    if (m_bImgAnimation)
    {
        double  dbInterval = getAbsoluteTime() - m_dbStartTime;
        m_hRatio = sin((dbInterval / 500.0L) * MATH_PI);
        if (dbInterval >= 245.0f)
        {
            m_hRatio = 1.0f;
            m_bImgAnimation = false;
        }
    }
}

void CAdsFrame::render(float elapsedTime)
{
    // Clear the screen.
    clear(CLEAR_COLOR_DEPTH, Vector4(0, 0, 0, 1), 1.0f, 0);

    // Draw SpriteBatch
    imgChanged();

    // Draw the forms.
    if (m_formSetting)
    {
        m_formSetting->draw();
    }

    if (m_activeForm)
    {
        m_activeForm->draw();
    }
}

void CAdsFrame::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    if (m_formNode)
    {
        switch (evt)
        {
        case Touch::TOUCH_PRESS:
            {
                m_touched = true;
                m_touchX = x;
            }
            break;
        case Touch::TOUCH_RELEASE:
            {
                m_touched = false;
                m_touchX = 0;
            }
            break;
        case Touch::TOUCH_MOVE:
            {
                int deltaX = x - m_touchX;
                m_touchX = x;

                // Yaw in world frame
                Matrix m;
                m_formNodeParent->getWorldMatrix().transpose(&m);
                Vector3 yaw;
                m.getUpVector(&yaw);
                m_formNodeParent->rotate(yaw, MATH_DEG_TO_RAD(deltaX * 0.5f));
            }
            break;
        default:
            break;
        };
    }
}

void CAdsFrame::beginAnimation()
{
    m_imgPreIndex = m_imgIndex;
    m_hRatio = 0.0f;
    m_bImgAnimation = true;
    m_dbStartTime = getAbsoluteTime();
}

void CAdsFrame::controlEvent(Control* control, EventType evt)
{
    if (evt == CLICK)
    {
        if (strcmp("rdoBind", control->getId()) == 0)
        {
            m_formIndex = 0;
            formChanged();
        }
        else if (strcmp("rdoTopup", control->getId()) == 0)
        {
            m_formIndex = 1;
            formChanged();
        }
        else if (strcmp("rdoProgram", control->getId()) == 0)
        {
            m_formIndex = 2;
            formChanged();
        }
        else if (strcmp("rdoImg1", control->getId()) == 0)
        {
            beginAnimation();
            m_imgIndex = 0;
        }
        else if (strcmp("rdoImg2", control->getId()) == 0)
        {
            beginAnimation();
            m_imgIndex = 1;
        }
        else if (strcmp("rdoImg3", control->getId()) == 0)
        {
            beginAnimation();
            m_imgIndex = 2;
        }
        else if (strcmp("rdoImg4", control->getId()) == 0)
        {
            beginAnimation();
            m_imgIndex = 3;
        }
        else if (strcmp("opacityButton", control->getId()) == 0)
        {
            float from[] = { 1.0f };
            float to[] = { 0.5f };
            control->createAnimationFromTo("opacityButton", Form::ANIMATE_OPACITY, from, to, Curve::LINEAR, 1000)->getClip()->play();
        }
    }
}
