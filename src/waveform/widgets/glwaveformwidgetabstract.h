#pragma once

#include "waveform/renderers/glwaveformrenderer.h"
#include "waveform/widgets/waveformwidgetabstract.h"
#include "widget/wglwidget.h"

class WWaveformViewer;

QT_FORWARD_DECLARE_CLASS(QString)

/// GLWaveformWidgetAbstract is a WaveformWidgetAbstract & WGLWidget. Its optional
/// member GLWaveformRenderer* m_pGlRenderer can implement a virtual method
/// onInitializeGL, which will be called from GLWaveformRenderer::initializeGL
/// (which overrides WGLWidget::initializeGL). This can be used for initialization
/// that must be deferred until the GL context has been initialized and that can't
/// be done in the constructor.
class GLWaveformWidgetAbstract : public WaveformWidgetAbstract, public WGLWidget {
  public:
    GLWaveformWidgetAbstract(const QString& group, QWidget* parent);

    WGLWidget* getGLWidget() override {
        return this;
    }

  protected:
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
    void initializeGL() override {
        if (m_pGlRenderer) {
            m_pGlRenderer->onInitializeGL();
        }
    }

    GLWaveformRenderer* m_pGlRenderer;

  private:
#ifdef MIXXX_USE_QOPENGL
    void handleEventFromWindow(QEvent* ev) override;
#endif

#endif // !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
};
