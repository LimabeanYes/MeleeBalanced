#include "toad.h"

////////////////////////
//   Item Functions   //
////////////////////////

bool OnGiveDamage(GOBJ *gobj)
{
    return true;
}

bool OnHitShieldBounce(GOBJ *item)
{
    Item_BounceOffShield(item);
    return false;
}

bool OnHitShieldDetermineDestroy(GOBJ *item)
{
    return true;
}

bool OnReflect(GOBJ *item)
{
    Item_ReflectVelocity(item);
    return false;
}


bool OnUnknown1(GOBJ *item)
{
    return true;
}

bool OnUnknown2(GOBJ *gobj)
{
    return true;
}

void OnUnknown3(GOBJ *gobj, GOBJ *fighter)
{
    Item_RemoveFighterReference(gobj, fighter);
    return;
}

////////////////////////
//  State Functions   //
////////////////////////

bool Fireball_AnimCB(GOBJ *item)
{
    return Item_DecLifeTimer(item);
}

bool Fireball_PhysCB(GOBJ *item)
{
    ItemData *item_data = item->userdata;
    itCommonAttr *attributes = item_data->common_attr;
    itCommonData *stc_itCommon = *stc_itPublicData;

    Item_ProjectileVelocityCalculate(item, attributes->fall_speed, attributes->fall_speed_max);
    Item_UpdateSpin(item, stc_itCommon->x68);

    return;
}

bool Fireball_CollCB(GOBJ *item)
{
    ItemData *item_data = (ItemData *)item->userdata;
    IceballAttr *attr = (IceballAttr *)item_data->itData->param_ext;
    JOBJ *jobj = (JOBJ *)item->hsd_object;

    // update item collision parameters
    Item_UpdatePositionCollision(item);

    // apply bounce physics and check if fireball bounced off of wall
    // this function will return 1 if the item collided with something
    // in addition it will make the item "bounce" off of any surface
    if (Item_Coll_Bounce(item))
    {
        // check to see if the current speed is within a certain threshold
        // if speed is slower than a given attribute, then destroy the fireball
        // by return 1
        float x_vel = item_data->self_vel.X;
        float y_vel = item_data->self_vel.Y;
        float speed = sqrtf(x_vel * x_vel + y_vel * y_vel);
        
        if (speed < attr->max_speed)
        {
            // if speed is lower than threshold, destroy fireball
            return 1;
        }
        else
        {
            // otherwise play fire sfx and spawn hit effect
            //Item_PlayOnDestroySFXAgain(item_data, MEX_SOUND_FIREBALL_DESTROY, 0x7f, 0x40);
            //Effect_SpawnAsync(item, &item_data->effect, 1, MEX_EFFECT_FIREBALL_FLAME, jobj);
        }
    }

    return false;
}

__attribute__((used)) 
static struct ItemState item_state_table[] =
{
    // state 0: 
    {
        .state = 0,
        .animCallback = Fireball_AnimCB,
        .physCallback = Fireball_PhysCB,
        .collCallback = Fireball_CollCB,
    }
};