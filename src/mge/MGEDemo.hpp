#ifndef MGEDEMO_HPP
#define MGEDEMO_HPP

#include <mge/core/AbstractGame.hpp>

class DebugHud;

class MGEDemo : public AbstractGame
{
private:
    DebugHud* m_hud; //hud display

    void updateHud();

    MGEDemo(const MGEDemo&);

    MGEDemo& operator=(const MGEDemo&);

protected:
    virtual void initializeScene();

    //override render to render the hud as well.
    virtual void render();

public:
    MGEDemo();

    virtual ~MGEDemo();

    virtual void initialize();
};

#endif // MGEDEMO_HPP
