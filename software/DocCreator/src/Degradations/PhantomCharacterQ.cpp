#include "PhantomCharacterQ.hpp"

#include "Utils/convertor.h"
#include <QString>

namespace dc {

  namespace PhantomCharacter {
    
    QImage
    phantomCharacter(const QImage &imgOriginal, Frequency frequency, const QString &phantomPatternsPath)
    {
      cv::Mat input = Convertor::getCvMat(imgOriginal);
      
      cv::Mat output = dc::PhantomCharacter::phantomCharacter(input, frequency, phantomPatternsPath.toStdString());
      
      return Convertor::getQImage(output);
    }

  } //namespace PhantomCharacter
    

  QImage
  PhantomCharacterQ::apply()
  {
    QImage resultImg = dc::PhantomCharacter::phantomCharacter(_original, _frequency, _phantomPatternsPath);

    emit imageReady(resultImg);

    return resultImg;
  }

  
} //namespace dc
