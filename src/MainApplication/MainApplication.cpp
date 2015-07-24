#include <MainApplication/MainApplication.hpp>

#include <Core/CoreMacros.hpp>

#include <iostream>
#include <QTimer>
#include <Engine/RadiumEngine.hpp>
#include <Engine/Renderer/Renderer.hpp>
#include <MainApplication/Gui/MainWindow.hpp>

namespace Ra
{
    MainApplication::MainApplication(int argc, char** argv)
            : QApplication(argc, argv)
            , m_mainWindow(nullptr)
            , m_engine(nullptr)
            , m_viewer(nullptr)
            , m_frameTimer(new QTimer(this))
    {
        // Boilerplate print.

        std::cerr << "*** Radium Engine Main App  ***" << std::endl;
#if defined (CORE_DEBUG)
        std::cerr << "(Debug Build) -- ";
#else
        std::cerr<<"(Release Build) -- ";
#endif

#if defined (ARCH_X86)
        std::cerr<<" 32 bits x86";
#elif defined (ARCH_X64)
        std::cerr << " 64 bits x64";
#endif
        std::cerr << std::endl;

        std::cerr << "Floating point format : ";
#if defined(CORE_USE_DOUBLE)
        std::cerr<<"double precision"<<std::endl;
#else
        std::cerr << "single precision" << std::endl;
#endif

        // Handle command line arguments.
        // TODO ( e.g fps limit)

        // Create default format for Qt.
        QSurfaceFormat format;
        format.setVersion(4, 4);
        format.setProfile(QSurfaceFormat::CoreProfile);
        format.setSamples(0);
        format.setDepthBufferSize(24);
        format.setStencilBufferSize(8);
        format.setSamples(16);
        format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
        QSurfaceFormat::setDefaultFormat(format);

        // Create main window.
        m_mainWindow.reset(new Gui::MainWindow);
        m_mainWindow->show();

        // Create engine
        m_engine.reset(new Engine::RadiumEngine);
        m_engine->initialize();

        // Wait for callback from  gui to  start the engine.
        // Maybe we should do it directly (i.e. grab the viewer from the main window).
        CORE_ASSERT(m_viewer != nullptr, "GUI or OpenGL was not initialized");

        m_frameTime = QTime::currentTime();

        connect(m_frameTimer, SIGNAL(timeout()), this, SLOT(radiumFrame()));
        m_frameTimer->start(1000.0 / 60.0);

    }

    void MainApplication::viewerReady(Gui::Viewer* viewer)
    {
        m_viewer = viewer;
        CORE_ASSERT( m_viewer->parent()->parent() == m_mainWindow.get(), "Viewer is not setup");
    }

    void MainApplication::radiumFrame()
    {
        QTime currentTime = QTime::currentTime();

        long elapsed = m_frameTime.msecsTo(currentTime);
        m_frameTime = currentTime;

        // Gather user input and dispatch it.

        // Run one frame of tasks

        // Draw call.
        m_viewer->update();

    }
    MainApplication::~MainApplication() {
        fprintf(stderr, "About to quit... Cleaning RadiumEngine memory.\n");
        m_engine->quit();
    }

}