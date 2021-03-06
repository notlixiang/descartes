/*
 * Software License Agreement (Apache License)
 *
 * Copyright (c) 2018, Southwest Research Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DENSE_PLANNER_H_
#define DENSE_PLANNER_H_

#include <descartes_core/path_planner_base.h>
#include <descartes_planner/planning_graph.h>

namespace descartes_planner
{
class DensePlanner : public descartes_core::PathPlannerBase
{
public:
  DensePlanner();

  virtual ~DensePlanner();

  virtual bool initialize(descartes_core::RobotModelConstPtr model);
  virtual bool initialize(descartes_core::RobotModelConstPtr model,
                          descartes_planner::CostFunction cost_function_callback);
  virtual bool setConfig(const descartes_core::PlannerConfig& config);
  virtual void getConfig(descartes_core::PlannerConfig& config) const;
  virtual bool planPath(const std::vector<descartes_core::TrajectoryPtPtr>& traj);
  virtual bool getPath(std::vector<descartes_core::TrajectoryPtPtr>& path) const;
  virtual bool addAfter(const descartes_core::TrajectoryPt::ID& ref_id, descartes_core::TrajectoryPtPtr tp);
  virtual bool addBefore(const descartes_core::TrajectoryPt::ID& ref_id, descartes_core::TrajectoryPtPtr tp);
  virtual bool remove(const descartes_core::TrajectoryPt::ID& ref_id);
  virtual bool modify(const descartes_core::TrajectoryPt::ID& ref_id, descartes_core::TrajectoryPtPtr tp);
  virtual int getErrorCode() const;
  virtual bool getErrorMessage(int error_code, std::string& msg) const;

  // Helper functions meant to access the underlying graph structure

  const PlanningGraph& getPlanningGraph() const
  {
    return *planning_graph_;
  }

protected:
  descartes_core::TrajectoryPt::ID getPrevious(const descartes_core::TrajectoryPt::ID& ref_id);
  descartes_core::TrajectoryPt::ID getNext(const descartes_core::TrajectoryPt::ID& ref_id);
  descartes_core::TrajectoryPtPtr get(const descartes_core::TrajectoryPt::ID& ref_id);
  bool updatePath();

protected:
  boost::shared_ptr<descartes_planner::PlanningGraph> planning_graph_;
  int error_code_;
  descartes_core::PlannerConfig config_;
  std::vector<descartes_core::TrajectoryPtPtr> path_;
  std::map<int, std::string> error_map_;
};

} /* namespace descartes_core */
#endif /* DENSE_PLANNER_H_ */
