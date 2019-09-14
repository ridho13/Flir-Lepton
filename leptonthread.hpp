#ifndef LEPTONTHREAD_HPP
#define LEPTONTHREAD_HPP

#include <cstdint>
#include <ctime>

#include <QImage>
#include <QPixmap>
#include <QThread>
#include <QtCore>

#include "temperature.hpp"

// Lepton configuration
constexpr int PACKET_SIZE{164};
constexpr int PACKET_SIZE_UINT16{PACKET_SIZE / 2};
constexpr int PACKETS_PER_FRAME{60};
constexpr int FRAME_SIZE_UINT16{PACKET_SIZE_UINT16 * PACKETS_PER_FRAME};

// Lepton communication timing parameters
constexpr uint16_t MaxResetsPerSegment{750};   // packet resets
constexpr uint16_t kMaxResetsPerFrame{30};     // segment resets
constexpr uint16_t kMaxResetsBeforeReboot{2};   // frame resets
constexpr uint32_t LeptonLoadTime{2000};     // 0.002 s = 2 ms = 2000 us
constexpr uint32_t LeptonResetTime{1000};    // 0.001 s = 1 ms = 3000 us
constexpr uint32_t LeptonRebootTime{750000};  // 0.75 s = 750 ms = 750000 us

class LeptonThread : public QThread {
  Q_OBJECT;

 public:
  LeptonThread();
  ~LeptonThread();

  void run();
  const int* colorMap;
 public slots:
  void performFFC();
  void rainMap();
  void greyMap();
  void ironMap();
  void snapImage();

 signals:
  void updateText(QString);
  void updateImage(QImage);

 private:
  // image
  QImage myImage;

  // buffer
  uint8_t result[PACKET_SIZE * PACKETS_PER_FRAME];
  uint16_t* frameBuffer;

  // temperature
  Temperature *m_temperature;
};

#endif  // LEPTONTHREAD_HPP
