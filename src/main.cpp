#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>
#include <bn_fixed_point.h>
#include <bn_vector.h>
#include <bn_log.h>

#include "bn_sprite_items_dot.h"
#include "movement.h"
#include "Center.h"
#include "orbiter.h"

// A scaling factor by which to reduce the force applied when orbiting
// Important for numerical stability


// Maximum number of orbiters allowed on the screen
static constexpr int MAX_ORBITERS = 30;

// Default starting posiiton and velocity for Orbiter
static constexpr bn::fixed_point ORBITER_START_POSIITON = {0, 0};
static constexpr bn::fixed_point ORBITER_START_VELOCITY = {0, 5};
//









/**
 * A center of mass to be orbited around. Position is controlled by the player.
 */


/**
 * An object that orbits around a center. Orbits using Hooke's law, as if attached by a 2D spring.
 * The stiffness of the spring in each dimension is center.mass() / FORCE_SCALE. 
 */


int main() {
    bn::core::init();

    Center center = Center({30, 40}, .05, 2);
    bn::vector<Orbiter, MAX_ORBITERS> orbiters = {};
    
    while(true) {
        // Add an orbiter when A is pressed if there's room
        if(bn::keypad::a_pressed()) {
            if(orbiters.size() < MAX_ORBITERS) {
                orbiters.push_back(Orbiter(ORBITER_START_POSIITON, ORBITER_START_VELOCITY, center));
            }
        }

        // Remove an orbiter when B is pressed if there's at least one
        if (bn::keypad::b_pressed()) {
            if(orbiters.size() > 0) {
                orbiters.pop_back();
            }
        }

        center.update();
        for(Orbiter& orbiter : orbiters) {
            orbiter.update();
        }

        bn::core::update();
    }
}