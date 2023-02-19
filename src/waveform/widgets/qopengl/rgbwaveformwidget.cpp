#include "waveform/widgets/qopengl/rgbwaveformwidget.h"

#include "waveform/renderers/qopengl/waveformrenderbackground.h"
#include "waveform/renderers/qopengl/waveformrenderbeat.h"
#include "waveform/renderers/qopengl/waveformrendererendoftrack.h"
#include "waveform/renderers/qopengl/waveformrendererpreroll.h"
#include "waveform/renderers/qopengl/waveformrendererrgb.h"
#include "waveform/renderers/qopengl/waveformrendermark.h"
#include "waveform/renderers/qopengl/waveformrendermarkrange.h"
#include "waveform/widgets/qopengl/moc_rgbwaveformwidget.cpp"

using namespace qopengl;

RGBWaveformWidget::RGBWaveformWidget(const QString& group, QWidget* parent)
        : WaveformWidget(group, parent) {
    addRenderer<WaveformRenderBackground>();
    addRenderer<WaveformRendererEndOfTrack>();
    addRenderer<WaveformRendererPreroll>();
    addRenderer<WaveformRenderMarkRange>();
    addRenderer<WaveformRendererRGB>();
    addRenderer<WaveformRenderBeat>();
    addRenderer<WaveformRenderMark>();

    m_initSuccess = init();
}

RGBWaveformWidget::~RGBWaveformWidget() {
}

void RGBWaveformWidget::castToQWidget() {
    m_widget = this;
}

void RGBWaveformWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
}