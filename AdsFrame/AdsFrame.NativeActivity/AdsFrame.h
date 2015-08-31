#ifndef _FORMFRAME_H_
#define _FORMFRAME_H_

#include <GamePlay.h>

using namespace gameplay;

class CAdsFrame : public Game, Control::Listener
{
public:
    CAdsFrame();

protected:
    void    initialize();
    void    finalize();
    void    update(float elapsedTime);
    void    render(float elapsedTime);
    void    touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);
    void    controlEvent(Control* control, EventType evt);

private:
    void    formChanged();
    void    imgChanged();
    void    createSampleForm();
    void    beginAnimation();

    /**
     * Draws the default "gameplay powered" splash screen.
     */
    void    drawSplash(void* param);

    Font*                       m_font;
    Scene*                      m_scene;
    Node*                       m_formNode;
    Node*                       m_formNodeParent;
    Form*                       m_formSetting;
    Form*                       m_activeForm;
    std::vector<Form*>          m_forms;
    std::vector<SpriteBatch*>   m_sBatchs;
    bool                        m_touched;
    int                         m_touchX;
    unsigned int                m_formIndex;
    unsigned int                m_imgIndex;
    unsigned int                m_imgPreIndex;
    bool                        m_bImgAnimation;///< 是否处在动画切换过程中
    float                       m_hRatio;       ///< 动画切换过程中新画面的显示比率0.0 ~ 1.0
    double                      m_dbStartTime;  ///< 动画开始的计时点
    std::vector<const char*>    m_formFiles;
    std::vector<const char*>    m_imgFiles;
};

#endif
