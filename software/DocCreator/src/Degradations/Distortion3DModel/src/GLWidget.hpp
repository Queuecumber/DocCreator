#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include "framework_global.h"

#include "OpenGL.hpp"
#if QT_VERSION < 0x050400
#include <QGLWidget>
#else
#include <QOpenGLWidget>
#endif
#include <QPoint>

#include "GLCamera.hpp"
#include "GLObject.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

class Mesh;

class FRAMEWORK_EXPORT GLWidget
  :
#if QT_VERSION < 0x050400
  public QGLWidget
#else
  public QOpenGLWidget
#endif
{
  Q_OBJECT

public:
  explicit GLWidget(QWidget *parent = nullptr);

  ~GLWidget();

  bool loadMesh(const QString &meshFilename);

  void computeTextureCoords();

  void setTexture(const QImage &image);

  bool saveMesh(const QString &outputMeshFilename);

  void setLightPos(float x, float y, float z);
  void setAmbientDiffuseSpecular(Eigen::Vector3f a,
                                 Eigen::Vector3f d,
                                 Eigen::Vector3f s);
  void setSpecularExponent(float se);
  void setUseTexture(bool onoff);
  void setTextureMatrix(const Eigen::Matrix3f &texMat);
  void applyTextureMatrix();
  void applyViewMatrix();
  void resetViewMatrix();

  void setUseBackgroundTexture(bool onoff);
  void setBackgroundTexture(const QImage &image);
  void setBackgroundTextureMatrix(const Eigen::Matrix3f &texMat);

  QImage takeScreenshot();
  QImage takeScreenshotHiRes();

  bool takeRandomScreenshots(const QString &prefix,
                             const QString &ext,
                             size_t numScreenshots,
                             float minPhy,
                             float maxPhy,
                             float minTheta,
                             float maxTheta);

signals:
  void hasTexCoords(bool onoff);
  void hasImage(bool onoff);

protected:
  virtual void initializeGL() override;

  virtual void resizeGL(int w, int h) override;

  virtual void paintGL() override;

  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *e) override;
  virtual void mouseReleaseEvent(QMouseEvent *e) override;
  virtual void mouseMoveEvent(QMouseEvent *e) override;
  virtual void wheelEvent(QWheelEvent *e) override;

  void printGLInfos();

  void initGLForMesh();

  void updateCameraLookAt();

  void getRayInWorld(QPoint pos,
                     Eigen::Vector3f &rayOrigin,
                     Eigen::Vector3f &rayDirection);

  void updateMeshGL();

  void setHiResSize(int &prevW, int &prevH);
  void resetLowResSize(int prevW, int prevH);

  void updateBackgroundTransformation();

private:
  typedef enum { MODE_MOVE_CAMERA = 0, MODE_SELECTION_VERTEX } Mode;

  /*


    QImage initialize(int pageId, int page_L_R, QImage srcInput);
    //void initializeDatabaseKHOI(int pageId, int page_L_R, QImage srcInput);
    //void initializeDatabaseWeb(int pageId, int page_L_R, int  imgId, QImage srcInput);
    void save(const char* filename, int w, int h);
    void keyboard(unsigned char key, int x, int y);
    void reshape (int w, int h);
    void display(void);
    void drawmodel(void);
    void init(void);
    GLuint genTexture(const QImage &img);
    void changePerspective();
    int _pageId, _page_L_R;
    QImage _srcInput;
  */

  Mode m_mode;

  QPoint m_lastMousePos;

  GLCamera m_camera;
  float m_camPhy;
  float m_camTheta;
  float m_camDist;
  Eigen::Vector3f m_camLookAt;
  float m_camFov;

  Eigen::Vector4f m_lightPos;
  Eigen::Vector3f m_ambient;
  Eigen::Vector3f m_diffuse;
  Eigen::Vector3f m_specular;
  float m_specularExponent;
  bool m_useTexture;
  Eigen::Matrix3f m_texMat;

  GLObject *m_object;
  GLMesh *m_meshGL;
  Shader m_program;

  GLuint m_textureId;
  GLuint m_samplerId;
  GLenum m_minFilter;
  GLenum m_magFilter;

  int m_tex_width;
  int m_tex_height;
  Mesh m_mesh;
  Mesh m_sphere;
  GLObject *m_sphereObject;
  GLMesh *m_sphereMeshGL;
  Shader m_sphereProgram;
  Eigen::Vector4f m_sphereColor;

  bool m_useBackground;
  bool m_useBackgroundTexture;
  Mesh m_backgroundMesh;
  GLObject *m_backgroundObject;
  GLMesh *m_backgroundMeshGL;
  Shader m_backgroundProgram;
  GLuint m_backgroundTextureId;
  GLuint m_backgroundSamplerId;
  GLenum m_backgroundMinFilter;
  GLenum m_backgroundMagFilter;
  Eigen::Matrix3f m_backgroundTexMat;

  std::vector<uint32_t> m_selectedVertices;
};

#endif /* ! GLWIDGET_HPP */
