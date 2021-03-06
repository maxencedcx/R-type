//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include <SFML/Window.hpp>
#include <engine/ForwardDeclaration.hpp>
#include <chrono>
#include <entities/ships/Ship.hpp>
#include "IWeapon.hpp"

namespace Entities {
    class AWeapon : public IWeapon {
    public:
        virtual bool shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position) = 0;

        virtual void setSpeed(sf::Vector2f const &speed) {
            this->xSpeed = speed.x;
            this->ySpeed = speed.y;
        };

        virtual void setXSpeed(float const &xSpeed) {
            this->xSpeed = xSpeed;
        }

        virtual void setYSpeed(float const &ySpeed) {
            this->ySpeed = ySpeed;
        }

        virtual void setCd(float const &value) {
            this->cd = value;
        }

        void setLastUse(std::chrono::time_point<std::chrono::system_clock> time) {
            this->lastUse = time;
        }

        virtual sf::Vector2f getSpeed() const {
            return {this->xSpeed, this->ySpeed};
        }

        virtual float getXSpeed() const {
            return this->xSpeed;
        }

        virtual float getYSpeed() const {
            return this->ySpeed;
        }

        virtual void upgrade(GRADE grade) {
            switch (grade) {
                case BRONZE:
                    if (this->ySpeed < 2)
                        this->ySpeed *= 1.1;
                    break;
                case SILVER:
                    if (this->cd > 0.1)
                        this->cd -= 0.1;
                    break;
                case GOLD:
                    this->damage *= 1.1;
                    break;
            }
        };

    protected:
        AWeapon(SCOPE *scope, std::string const &projectilePath, float const cd, int const damage,
                float const xSpeed, float const ySpeed, Entities::Ship::TEAM originTeam, network::protocol::Type type)
                : scope(scope), projectilePath(projectilePath), cd(cd), damage(damage), xSpeed(xSpeed), ySpeed(ySpeed),
                  originTeam(originTeam) {
            this->type = type;
            this->lastUse = std::chrono::system_clock::from_time_t(0);
        };

        virtual void spawnLasers(sf::Vector2f const &position) = 0;

        SCOPE *scope;
        float cd;
        int damage;
        std::chrono::time_point<std::chrono::system_clock> lastUse;
        std::string projectilePath;
        float xSpeed;
        float ySpeed;
        Entities::Ship::TEAM originTeam;
        network::protocol::Type type;
    };
}
