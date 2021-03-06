/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  title.cpp                                   *
 *  Widget that holds title ui animation        *
 *  and utilizes box2D.                         *
 *                                              *
 ************************************************/

#include "title.h"
#include "ui_title.h"
#include "Box2D/Box2D.h"
#include <stdio.h>
#include <QTimer>

/**
 * @brief Title::Title
 * @param parent
 * Title page that displays our animation
 * Our Use of Box2D
 */
Title::Title(QWidget *parent) :
    QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    ui(new Ui::Title)
{
    ui->setupUi(this);

    //    this->setStyleSheet("{background-image: url(:/Resources/cardClubs10.png);}");
    gameStart = true;

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 300.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(800.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 150.0f);
    body = world.CreateBody(&bodyDef);

    body2 = world.CreateBody(&bodyDef);
    body3 = world.CreateBody(&bodyDef);
    body4 = world.CreateBody(&bodyDef);


    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Set the box restitution
    fixtureDef.restitution = 1.0f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    body2->CreateFixture(&fixtureDef);
    body3->CreateFixture(&fixtureDef);
    body4->CreateFixture(&fixtureDef);
}

/**
 * @brief Title::~Title
 * Title destructor
 */
Title::~Title()
{
    delete ui;
}

/**
 * @brief Title::startAnimation
 * Starts the title animation
 */
void Title::startAnimation()
{

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // This is our little game loop.
    {
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world.Step(timeStep, velocityIterations, positionIterations);

        // Now print the position and angle of the body.
        b2Vec2 position = body->GetPosition();
        b2Vec2 position2 = body2->GetPosition();
        b2Vec2 position3 = body3->GetPosition();
        b2Vec2 position4 = body4->GetPosition();

        //float32 angle = body->GetAngle();

       // printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        int textHeight = int(position.y);
        int textHeight2 = int(position2.y);

        int textHeight3 = int(position3.y);

        int textHeight4 = int(position4.y);

        QTimer::singleShot(1, [this, textHeight, textHeight2, textHeight3, textHeight4] () {
                           updateCard1(textHeight); updateCard2(textHeight2); updateCard3(textHeight3); updateCard4(textHeight4);
                           });

        QTimer::singleShot(1, this, SLOT(startAnimation()));

    }
}
