// Filename: pointerToVoid.h
// Created by:  drose (27Sep04)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#ifndef POINTERTOVOID_H
#define POINTERTOVOID_H

#include "pandabase.h"
#include "pnotify.h"
#include "memoryBase.h"
#include "atomicAdjust.h"

#include <algorithm>

////////////////////////////////////////////////////////////////////
//       Class : PointerToVoid
// Description : This is the non-template part of the base class for
//               PointerTo and ConstPointerTo.  It is necessary so we
//               can keep a pointer to a non-template class within the
//               ReferenceCount object, to implement weak reference
//               pointers--we need to have something to clean up when
//               the ReferenceCount object destructs.
//
//               This is the base class for PointerToBase<T>.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDAEXPRESS PointerToVoid : public MemoryBase {
protected:
  INLINE PointerToVoid();
  INLINE ~PointerToVoid();

private:
  INLINE PointerToVoid(const PointerToVoid &copy);

PUBLISHED:
  INLINE bool is_null() const;
  INLINE size_t get_hash() const;

public:
  // These comparison functions are common to all things PointerTo, so
  // they're defined up here.
  INLINE bool operator < (const void *other) const;
  INLINE bool operator < (const PointerToVoid &other) const;

  INLINE bool operator == (const PointerToVoid &other) const;
  INLINE bool operator != (const PointerToVoid &other) const;

  INLINE void swap(PointerToVoid &other) NOEXCEPT;

protected:
  // Within the PointerToVoid class, we only store a void pointer.
  // This is actually the (To *) pointer that is typecast to (void *)
  // from the derived template classes.

  // It is tempting to try to store a (ReferenceCount *) pointer here,
  // but this is not useful because it prohibits defining, say,
  // PT(PandaNode), or a PointerTo any class that inherits virtually
  // from ReferenceCount.  (You can't downcast past a virtual
  // inheritance level, but you can always cross-cast from a void
  // pointer.)
  AtomicAdjust::Pointer _void_ptr;
};

#include "pointerToVoid.I"

#endif
