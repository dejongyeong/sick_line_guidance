/*
 * ExploreLineState implements the state to explore a line for sick_line_guidance_demo.
 * As long as ols does not detect a line, cmd_vel messages are published to search a line.
 * Currently, the TurtleBot just moves straight forwared until a line is detected.
 * Input: ols messages
 * Output: cmd_vel messages
 *
 * Copyright (C) 2019 Ing.-Buero Dr. Michael Lehning, Hildesheim
 * Copyright (C) 2019 SICK AG, Waldkirch
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of SICK AG nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission
 *     * Neither the name of Ing.-Buero Dr. Michael Lehning nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *      Authors:
 *         Michael Lehning <michael.lehning@lehning.de>
 *
 *  Copyright 2019 SICK AG
 *  Copyright 2019 Ing.-Buero Dr. Michael Lehning
 *
 */
#ifndef __SICK_LINE_GUIDANCE_DEMO_EXPLORE_LINE_STATE_H_INCLUDED
#define __SICK_LINE_GUIDANCE_DEMO_EXPLORE_LINE_STATE_H_INCLUDED

#include <boost/thread.hpp>
#include <nav_msgs/Odometry.h>
#include "sick_line_guidance/OLS_Measurement.h"
#include "sick_line_guidance_demo/robot_fsm_context.h"

namespace sick_line_guidance_demo
{
  /*
   * ExploreLineState implements the state to explore a line for sick_line_guidance_demo.
   * As long as ols does not detect a line, cmd_vel messages are published to search a line.
   * Currently, the TurtleBot just moves straight forwared until a line is detected.
   * Input: ols messages
   * Output: cmd_vel messages
   */
  class ExploreLineState
  {
  public:

    /*
     * Constructor
     * @param[in] nh ros handle
     * @param[in] context shared fsm context
     */
    ExploreLineState(ros::NodeHandle* nh=0, RobotFSMContext* context = 0);
  
    /*
     * Destructor
     */
    ~ExploreLineState();
  
    /*
     * Clears all internal states
     */
    void clear(void);
  
    /*
     * Runs the explore line state until line is detected (or a fatal error occures).
     * @return FOLLOW_LINE in case of line detected, or EXIT in case ros::ok()==false.
     */
    RobotFSMContext::RobotState run(void);

  protected:

    /*
     * member data
     */

    RobotFSMContext* m_fsm_context; // shared state context
  
    /*
     * Configuration
     */
  
    double m_exploreSpeed;          // default linear velocity to explore a line
    ros::Rate m_explore_line_rate;  // frequency to update explort line state, default: 20 Hz
    double m_ols_message_timeout;   // timeout for ols messages: robot stops and waits, if last ols message was received more than <timeout> seconds ago
    double m_odom_message_timeout;  // timeout for odom messages: robot stops and waits, if last ols message was received more than <timeout> seconds ago

  }; // class ExploreLineState

} // namespace sick_line_guidance_demo
#endif // __SICK_LINE_GUIDANCE_DEMO_EXPLORE_LINE_STATE_H_INCLUDED

