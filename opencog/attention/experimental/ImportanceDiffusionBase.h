/*
 * ImportanceDiffusionBase.cc
 *
 * Copyright (C) 2014-2016 Cosmo Harrigan
 * All Rights Reserved
 *
 * Written by Cosmo Harrigan
 * written by Misgana Bayetta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef IMPORTANCEDIFFUSIONBASE_H
#define IMPORTANCEDIFFUSIONBASE_H

#include <string>
#include <stack>
#include <math.h>
#include <opencog/atomspace/AtomSpace.h>
#include <opencog/truthvalue/AttentionValue.h>
#include <opencog/cogserver/server/Agent.h>
#include <opencog/util/Logger.h>
#include <opencog/util/RandGen.h>
#include <opencog/attention/SpreadDecider.h>

namespace opencog
{
/** \addtogroup grp_attention
 *  @{
 */

class CogServer;

/**
 * Common methods and variables used for Importance diffusion.
 */
class ImportanceDiffusionBase : public Agent
{
private:
    int sleep_time_ms;

protected:
    float maxSpreadPercentage;
    float hebbianMaxAllocationPercentage;
    bool spreadHebbianOnly;
    SpreadDecider* spreadDecider;

    typedef struct DiffusionEventType
    {
        Handle source;
        Handle target;
        AttentionValue::sti_t amount;
    } DiffusionEventType;

    std::stack<DiffusionEventType> diffusionStack;
    void processDiffusionStack();

    virtual void diffuseAtom(Handle);

    HandleSeq diffusionSourceVector(bool af_only);
    HandleSeq incidentAtoms(Handle);
    HandleSeq hebbianAdjacentAtoms(Handle);
    std::map<Handle, double> probabilityVector(HandleSeq);
    AttentionValue::sti_t calculateDiffusionAmount(Handle);
    float calculateHebbianDiffusionPercentage(Handle);
    float calculateIncidentDiffusionPercentage(Handle);
    std::map<Handle, double> probabilityVectorIncident(HandleSeq);
    std::map<Handle, double> probabilityVectorHebbianAdjacent(Handle, HandleSeq);
    std::map<Handle, double> combineIncidentAdjacentVectors(
            std::map<Handle, double>, std::map<Handle, double>);
    void tradeSTI(DiffusionEventType);
    void updateMaxSpreadPercentage();

    virtual void spreadImportance() = 0;

public:
    enum { HYPERBOLIC, STEP };
    void setSpreadDecider(int type, float shape = 30);
    void setMaxSpreadPercentage(float);
    void setHebbianMaxAllocationPercentage(float);
    void setSpreadHebbianOnly(bool);

    ImportanceDiffusionBase(CogServer&);
    virtual ~ImportanceDiffusionBase();

    int get_sleep_time(){
        return sleep_time_ms;
    }

    void set_sleep_time(int ms){
      sleep_time_ms = ms;
    }

}; // class

/** @}*/
} // namespace

#endif /* IMPORTANCEDIFFUSIONBASE_H */

