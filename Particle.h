#ifndef PARTICLE_H
#define PARTICLE_H
#include <memory>

#include "Vector2D.h"
#include <string>

class Particle {
private:
    static int nextId;
    int id;
    std::string name;
    double mass;
    double radius;
    Vector2D position;
    Vector2D velocity;
public:
    Particle (const std::string name,
        double mass,
        double radius,
        const Vector2D& position = Vector2D(),
        const Vector2D& velocity =  Vector2D())
            :
    name(name),
    mass(mass), radius(radius),
    position(position), velocity(velocity) {
        id=nextId;
    }
    Particle (const Particle& other) :
    id(nextId++),
    name(other.name),
    mass(other.mass),
    radius(other.radius),
    position(other.position),
    velocity(other.velocity) {}

    Particle& operator=(const Particle& other) {
        if (this!=&other) {
            name=other.name;
            mass=other.mass;
            radius=other.radius;
            position=other.position;
            velocity=other.velocity;
        }
        return *this;
    }
    virtual ~Particle() {}

    int getId() const { return id; }
    const std::string& getName() const { return name; }
    double getMass() const { return mass; }
    double getRadius() const { return radius; }
    const Vector2D& getPosition() const { return position; }
    const Vector2D& getVelocity() const { return velocity; }

    void setName(const std::string& name){this->name=name;}
    void setMass(double mass){this->mass=mass;}
    void setRadius(double radius){this->radius=radius;}
    void setPosition(const Vector2D& position) {
        this->position=position;
    }
    void setVelocity(const Vector2D& velocity) {
        this->velocity=velocity;
    }

    virtual void update(double dt) {
        position.setX(position.getX()+velocity.getX()*dt);
        position.setY(position.getY()+velocity.getY()*dt);
    }

    bool collidesWith(const Particle& other) const {
        double dx=position.getX()-other.position.getX();
        double dy=position.getY()-other.position.getY();
        double distance=std::sqrt(dx*dx + dy*dy);
        return distance<(radius+other.radius);
    }

    void handleCollision(Particle& other) {
        Vector2D collisionDir(other.position.getX()-position.getX(),
            other.position.getY()-position.getY());
        collisionDir.normalize();

        double v1=velocity.getX()*collisionDir.getX()+velocity.getY()*collisionDir.getY();
        double v2=other.velocity.getX()*collisionDir.getX()+other.velocity.getY()*collisionDir.getY();

        double newV1=(v1*(mass-other.mass)+2*other.mass*v2)/(mass+other.mass);
        double newV2=(v2*(other.mass-mass)+2*mass*v1)/(mass+other.mass);

        velocity.setX(velocity.getX()+(newV1-v1)*collisionDir.getX());
        velocity.setY(velocity.getY()+(newV1-v1)*collisionDir.getY());

        other.velocity.setX(other.velocity.getX()+(newV2-v2)*collisionDir.getX());
        other.velocity.setY(other.velocity.getY()+(newV2-v2)*collisionDir.getY());

        double overlap=radius+other.radius-collidesWith(other);
        if (overlap>0) {
            position.setX(position.getX()-collisionDir.getX()*overlap*0.5);
            position.setY(position.getY()-collisionDir.getY()*overlap*0.5);
            other.position.setX(other.position.getX()-collisionDir.getX()*overlap*0.5);
            other.position.setY(other.position.getY()-collisionDir.getY()*overlap*0.5);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Particle& p) {
            os<<"Particle"<<p.id<<"("<<p.name<<"):"
            <<"mass="<<p.mass<<", radius="<<p.radius
            <<", position="<<p.position
            <<", velocity="<<p.velocity;
            return os;
        }


};
int Particle::nextId=1;
#endif
