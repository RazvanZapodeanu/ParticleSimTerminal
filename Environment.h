#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Particle.h"
#include <vector>
#include <memory>

class Environment {
private:
    double height;
    double width;
    std::vector<std::shared_ptr<Particle>> particles;
public:
    Environment(double width=100.0,double height=100.0)
        :width(width), height(height) {}
    Environment(const Environment& other)
        :width(other.width), height(other.height) {
        for (const auto& p:other.particles) {
            particles.push_back(std::make_shared<Particle>(*p));
        }
    }

    Environment& operator=(const Environment& other) {
        if (this!=&other) {
            width=other.width;
            height=other.height;

            particles.clear();

            for (const auto& p:other.particles) {
                particles.push_back(std::make_shared<Particle>(*p));
            }
        }
        return *this;
    }

    ~Environment() {}

    double getWidth() const { return width; }
    double getHeight() const { return height; }
    const std::vector<std::shared_ptr<Particle>>& getParticles() const { return particles; }


    void setWidth(double newWidth) { width = newWidth; }
    void setHeight(double newHeight) { height = newHeight; }


    void addParticle(const Particle& particle) {
        particles.push_back(std::make_shared<Particle>(particle));
    }

    void removeParticle(int id) {
        for (auto it = particles.begin(); it != particles.end(); ++it) {
            if ((*it)->getId() == id) {
                particles.erase(it);
                break;
            }
        }
    }
    void update(double dt) {

        for (auto& p : particles) {
            p->update(dt);


            Vector2D pos = p->getPosition();
            Vector2D vel = p->getVelocity();
            double r = p->getRadius();

            if (pos.getX() - r < 0) {
                p->setPosition(Vector2D(r, pos.getY()));
                p->setVelocity(Vector2D(-vel.getX(), vel.getY()));
            }
            else if (pos.getX() + r > width) {
                p->setPosition(Vector2D(width - r, pos.getY()));
                p->setVelocity(Vector2D(-vel.getX(), vel.getY()));
            }

            if (pos.getY() - r < 0) {
                p->setPosition(Vector2D(pos.getX(), r));
                p->setVelocity(Vector2D(vel.getX(), -vel.getY()));
            }
            else if (pos.getY() + r > height) {
                p->setPosition(Vector2D(pos.getX(), height - r));
                p->setVelocity(Vector2D(vel.getX(), -vel.getY()));
            }
        }


        for (size_t i = 0; i < particles.size(); ++i) {
            for (size_t j = i + 1; j < particles.size(); ++j) {
                if (particles[i]->collidesWith(*particles[j])) {
                    particles[i]->handleCollision(*particles[j]);
                }
            }
        }
    }


    friend std::ostream& operator<<(std::ostream& os, const Environment& env) {
        os << "Environment: width=" << env.width << ", height=" << env.height << "\n";
        os << "Particles (" << env.particles.size() << "):\n";
        for (const auto& p : env.particles) {
            os << "  " << *p << "\n";
        }
        return os;
    }

};


#endif
