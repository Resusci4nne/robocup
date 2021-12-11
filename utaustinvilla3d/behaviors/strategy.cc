#include "naobehavior.h"
#include "../rvdraw/rvdraw.h"

extern int agentBodyType;

/*
 * Real game beaming.
 * Filling params x y angle
 */
void NaoBehavior::beam( double& beamX, double& beamY, double& beamAngle ) {
    beamX = -HALF_FIELD_X + worldModel->getUNum();
    beamY = 0;
    beamAngle = 0;
}


SkillType NaoBehavior::selectSkill() 
{
    VecPosition Posball=worldModel->getBall();
    VecPosition target[4]={Posball+VecPosition(-0.5,0,0),Posball+VecPosition(4,0,0),Posball+VecPosition(0,1,0),Posball+VecPosition(0,-1,0)};
    // worldModel->getRVSender()->clear(); // erases drawings from previous cycle
    // worldModel->getRVSender()->drawPoint("ball", ball.getX()+1, ball.getY(), 10.0f, RVSender::MAGENTA);
    double a[4][4];
    double bmin[4]={1000,1000,1000,1000};
    int bnum[4]={-1};
    for(int i = 0; i < 4; ++i) 
    {
        VecPosition temp;
        int playerNum =  WO_TEAMMATE1 + i;
        if (worldModel->getUNum() == playerNum) {
            temp = worldModel->getMyPosition();
            
        } else {
            WorldObject* teammate = worldModel->getWorldObject(WO_TEAMMATE1 + i );
            if (teammate->validPosition) {
               temp = teammate->pos;
            } else {
                continue;
            }}
           for(int j=0;j<4;j++)
          {
              a[i][j] =temp.getDistanceTo(target[j]);
              if(worldModel->getFallenTeammate(WO_TEAMMATE1 + i ))
              {
                  a[i][j]+=1;

              }
          } 
        }
    

    for(int j=0;j<4;j++)
    {
        for(int i=0;i<4;i++)
        {
            if(a[i][j]<bmin[j])
            {
                bmin[j]=a[i][j];
                bnum[j]=i;
            }
            
        }
        for(int x=0;x<4;x++)
            {
                a[bnum[j]][x]=10000;
            }
    }
    // cout<< worldModel->getUNum() << "   " << bnum[0] << bnum[1] << bnum[2] << bnum[3] << endl;
    // worldModel->getRVSender()->clearStaticDrawings();
    // for(int i=0;i<4;i++)
    // {
    // worldModel->getRVSender()->drawPoint("ball", target[i].getX(), target[i].getY(), 10.0f, RVSender::MAGENTA);
    // worldModel->getRVSender()->drawText(to_string(bnum[i]), target[i].getX(), target[i].getY(), RVSender::MAGENTA);
    // }
    for(int i=0;i<4;i++)
    {
        int playerNum =  WO_TEAMMATE1 + bnum[i];
        if (worldModel->getUNum() == playerNum) 
         {
        //     if(worldModel->getUNum() == WO_TEAMMATE3)
        //      worldModel->getRVSender()->drawPoint("3333", target[i].getX(), target[i].getY(), 10.0f, RVSender::RED);
             return goToTarget(collisionAvoidance(true, false, false, 1, .5,target[i], true));
        }
      
    }
}
    
   


    /* if (worldModel->getUNum() == WO_TEAMMATE2)
     {

          if (me.getDistanceTo(ball) > 1.5 )
             return goToTarget(collisionAvoidance(true, false, false, 1, .5,target1, true)); 
        else
           return kickBall(KICK_DRIBBLE, goal); 
    }


    else if (worldModel->getUNum() == WO_TEAMMATE1)
    { 

       
        if(me.getDistanceTo(ball) > 1 && me.getDistanceTo(center) < 1)
        return SKILL_STAND;

        else if(me.getDistanceTo(center) > 1)
        {
            return goToTarget(collisionAvoidance(true, false, false, 1, .5,center, true));
        }
        else if(me.getDistanceTo(ball) < 1 && me.getDistanceTo(center) < 1)
        {
            return kickBall(KICK_IK, target);}
    }

    else{return SKILL_STAND;}*/
        




    // My position and angle
    //cout << worldModel->getUNum() << ": " << worldModel->getMyPosition() << ",\t" << worldModel->getMyAngDeg() << "\n";

    // Position of the ball
    //cout << worldModel->getBall() << "\n";

    // Example usage of the roboviz drawing system and RVSender in rvdraw.cc.
    // Agents draw the position of where they think the ball is
    // Also see example in naobahevior.cc for drawing agent position and
    // orientation.
    /*
    worldModel->getRVSender()->clear(); // erases drawings from previous cycle
    worldModel->getRVSender()->drawPoint("ball", ball.getX(), ball.getY(), 10.0f, RVSender::MAGENTA);
    */

    // ### Demo Behaviors ###

    // Walk in different directions
    //return goToTargetRelative(VecPosition(1,0,0), 0); // Forward
    //return goToTargetRelative(VecPosition(-1,0,0), 0); // Backward
    //return goToTargetRelative(VecPosition(0,1,0), 0); // Left
    //return goToTargetRelative(VecPosition(0,-1,0), 0); // Right
    //return goToTargetRelative(VecPosition(1,1,0), 0); // Diagonal
    //return goToTargetRelative(VecPosition(0,1,0), 90); // Turn counter-clockwise
    //return goToTargetRelative(VecPdosition(0,-1,0), -90); // Turn clockwise
    //return goToTargetRelative(VecPosition(1,0,0), 15); // Circle

    // Walk to the ball
    //return goToTalrget(ball);

    // Turn in place to face bal
    /*double distance, angle;
    getTargetDistanceAndAngle(ball, distance, angle);
    if (abs(angle) > 10) {
      return goToTargetRelative(VecPosition(), angle);
    } else {
      return SKILL_STAND;
    }*/

    // Walk to ball while always facing forward
    //return goToTargetRelative(worldModel->g2l(ball), -worldModel->getMyAngDeg());

    // Dribble ball toward opponent's goal
    //return kickBall(KICK_DRIBBLE, VecPosition(HALF_FIELD_X, 0, 0));

    // Kick ball toward opponent's goal
    //return kickBall(KICK_FORWARD, VecPosition(HALF_FIELD_X, 0, 0)); // Basic kick
    //return kickBall(KICK_IK, VecPosition(HALF_FIELD_X, 0, 0)); // IK kick

    // Just stand in place
    //return SKILL_STAND;

    // Demo behavior where players form a rotating circle and kick the ball
    // back and forth
   // return demoKickingCircle();



/*
 * Demo behavior where players form a rotating circle and kick the ball
 * back and forth
 */
// SkillType NaoBehavior::demoKickingCircle() {
//     // Parameters for circle
//     VecPosition center = VecPosition(-HALF_FIELD_X/2.0, 0, 0);
//    double circleRadius = 5.0;
//     double rotateRate = 2.5;

//     // Find closest player to ball
//     int playerClosestToBall = -1;
//     double closestDistanceToBall = 10000;
//     for(int i = WO_TEAMMATE1; i < WO_TEAMMATE1+NUM_AGENTS; ++i) {
//         VecPosition temp;
//         int playerNum = i - WO_TEAMMATE1 + 1;
//         if (worldModel->getUNum() == playerNum) {
//             // This is us
//             temp = worldModel->getMyPosition();
//         } else {
//             WorldObject* teammate = worldModel->getWorldObject( i );
//             if (teammate->validPosition) {
//                temp = teammate->pos;
//             } else {
//                 continue;
//             }
//         }
//         temp.setZ(0);

//         double distanceToBall = temp.getDistanceTo(ball);
//         if (distanceToBall < closestDistanceToBall) {
//             playerClosestToBall = playerNum;
//             closestDistanceToBall = distanceToBall;
//         }
//     }

//     if (playerClosestToBall == worldModel->getUNum()) {
//         // Have closest player kick the ball toward the center
//         return kickBall(KICK_FORWARD, center);
//     } else {
//         // Move to circle position around center and face the center
//        VecPosition localCenter = worldModel->g2l(center);
//         SIM::AngDeg localCenterAngle = atan2Deg(localCenter.getY(), localCenter.getX());

//         // Our desired target position on the circle
//         // Compute target based on uniform number, rotate rate, and time
//         VecPosition target = center + VecPosition(circleRadius,0,0).rotateAboutZ(360.0/(NUM_AGENTS-1)*(worldModel->getUNum()-(worldModel->getUNum() > playerClosestToBall ? 1 : 0)) + worldModel->getTime()*rotateRate);

//         // Adjust target to not be too close to teammates or the ball
//         target = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, target, true/*keepDistance*/);

//      if (me.getDistanceTo(target) < .25 && abs(localCenterAngle) <= 10) {
//             // Close enough to desired position and orientation so just stand
//             return SKILL_STAND;
//         } else if (me.getDistanceTo(target) < .5) {
//             // Close to desired position so start turning to face center
//           return goToTargetRelative(worldModel->g2l(target), localCenterAngle);
//        } else {
//             // Move toward target location
//            return goToTarget(target);
//         }
//     }
// }