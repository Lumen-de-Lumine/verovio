/////////////////////////////////////////////////////////////////////////////
// Name:        rest.h
// Author:      Laurent Pugin
// Created:     2011
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_REST_H__
#define __VRV_REST_H__

#include "atts_mensural.h"
#include "durationinterface.h"
#include "layerelement.h"
#include "positioninterface.h"

namespace vrv {

//----------------------------------------------------------------------------
// Rest
//----------------------------------------------------------------------------

/**
 * This class models the MEI <rest> element.
 */
class Rest : public LayerElement,
             public DurationInterface,
             public PositionInterface,
             public AttColor,
             public AttRelativesize,
             public AttRestVisMensural {
public:
    /**
     * @name Constructors, destructors, reset and class name methods
     * Reset method resets all attribute classes
     */
    ///@{
    Rest();
    virtual ~Rest();
    virtual void Reset();
    virtual std::string GetClassName() const { return "Rest"; }
    virtual ClassId GetClassId() const { return REST; }
    ///@}

    /**
     * Add an element to a rest.
     * Only Dots elements will be actually added to the rest.
     */
    virtual void AddChild(Object *object);

    virtual PositionInterface *GetPositionInterface() { return dynamic_cast<PositionInterface *>(this); }

    virtual DurationInterface *GetDurationInterface() { return dynamic_cast<DurationInterface *>(this); }

    /** Override the method since alignment is required */
    virtual bool HasToBeAligned() const { return true; }
                 
    /**
     *
     */
    int GetDefaultLoc(bool hasMultipleLayer, bool isFirstLayer);

    //----------//
    // Functors //
    //----------//

    /**
     * See Object::CalcDots
     */
    virtual int CalcDots(FunctorParams *functorParams);

    /**
     * See Object::PrepareLayerElementParts
     */
    virtual int PrepareLayerElementParts(FunctorParams *functorParams);

    /**
     * See Object::ResetDrawing
     */
    virtual int ResetDrawing(FunctorParams *functorParams);

    /**
     * See Object::ResetHorizontalAlignment
     */
    virtual int ResetHorizontalAlignment(FunctorParams *functorParams);

private:
    //
public:
    //
private:
};

} // namespace vrv

#endif
