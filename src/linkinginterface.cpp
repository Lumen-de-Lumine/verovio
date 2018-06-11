/////////////////////////////////////////////////////////////////////////////
// Name:        linkinginterface.cpp
// Author:      Laurent Pugin
// Created:     2018
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "linkinginterface.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "functorparams.h"
#include "measure.h"
#include "vrv.h"

namespace vrv {

//----------------------------------------------------------------------------
// LinkingInterface
//----------------------------------------------------------------------------

LinkingInterface::LinkingInterface() : Interface(), AttLinking()
{
    RegisterInterfaceAttClass(ATT_LINKING);

    Reset();
}

LinkingInterface::~LinkingInterface() {}

void LinkingInterface::Reset()
{
    ResetLinking();

    m_next = NULL;
    m_nextUuid = "";
}

void LinkingInterface::SetNextLink(Object *next)
{
    assert(!m_next);
    m_next = next;
}

void LinkingInterface::SetUuidStr()
{
    if (this->HasNext()) {
        m_nextUuid = ExtractUuidFragment(this->GetNext());
    }
}

Measure *LinkingInterface::GetNextMeasure()
{
    if (!m_next) return NULL;
    return dynamic_cast<Measure *>(this->m_next->GetFirstParent(MEASURE));
}

//----------------------------------------------------------------------------
// Interface pseudo functor (redirected)
//----------------------------------------------------------------------------

int LinkingInterface::InterfacePrepareLinking(FunctorParams *functorParams, Object *object)
{
    PrepareLinkingParams *params = dynamic_cast<PrepareLinkingParams *>(functorParams);
    assert(params);

    // This should not happen?
    if (params->m_fillList == false) {
        return FUNCTOR_CONTINUE;
    }

    this->SetUuidStr();
    
    if (!m_nextUuid.empty()) {
        params->m_nextUuidPairs.push_back(std::make_pair(this, m_nextUuid));
    }
    
    return FUNCTOR_CONTINUE;
}
    

int LinkingInterface::InterfaceFillStaffCurrentTimeSpanning(FunctorParams *functorParams, Object *object)
{
    FillStaffCurrentTimeSpanningParams *params = dynamic_cast<FillStaffCurrentTimeSpanningParams *>(functorParams);
    assert(params);
    
    
    // Only Dir and Dynam can be spanning with @next (extender)
    if (!object->Is({DIR, DYNAM})) {
        return FUNCTOR_CONTINUE;
    }
    
    // Only target control events are supported
    if (!this->GetNextLink() || !this->GetNextLink()->IsControlElement()) {
        return FUNCTOR_CONTINUE;
    }

    params->m_timeSpanningElements.push_back(object);

    return FUNCTOR_CONTINUE;
}


int LinkingInterface::InterfaceResetDrawing(FunctorParams *functorParams, Object *object)
{
    m_next = NULL;
    m_nextUuid = "";
    return FUNCTOR_CONTINUE;
}

} // namespace vrv
