/*
 *  BGFitness.h
 *  Copyright 2009 Jean-Francois Dupuis.
 *
 *  This file is part of EvoBG.
 *  
 *  EvoBG is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  EvoBG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with EvoBG.  If not, see <http://www.gnu.org/licenses/>.
 *  
 *  This file was created by Jean-Francois Dupuis on 27/05/09.
 */

#ifndef BGFitness_H
#define BGFitness_H

#include <beagle/FitnessSimple.hpp>
#include <string>
#include <vector>
#include <PACC/Math.hpp>
#include "LogFitness.h"
#include "GrowingBG.h"

class BGFitness : public LogFitness {
public:
	//! BGFitness allocator type.
	typedef Beagle::AllocatorT<BGFitness,LogFitness::Alloc>
	Alloc;
	//!< BGFitness handle type.
	typedef Beagle::PointerT<BGFitness,LogFitness::Handle>
	Handle;
	//!< BGFitness bag type.
	typedef Beagle::ContainerT<BGFitness,LogFitness::Bag>
	Bag;
	
	BGFitness(float inFitness = 0) : LogFitness(inFitness), mOriginalFitness(inFitness) {}
	~BGFitness() {}
	
	void addStateMatrix(const PACC::Matrix& inMatrix) { mStateMatrices.push_back(inMatrix); }

	virtual void read(PACC::XML::ConstIterator inIter);
	virtual void write(PACC::XML::Streamer& ioStreamer, bool inIndent) const;
	
	BGFitness& operator=(const BGFitness& inRightFitness);
	
	void setBondGraph( GrowingBG::Handle inBondGraph) { mBondGraph = inBondGraph; }
	GrowingBG::Handle getBondGraph() { return mBondGraph; }
	
	void setSimplifiedBondGraph( GrowingBG::Handle inBondGraph) { mSimplifiedBondGraph = inBondGraph; }
	GrowingBG::Handle getSimplifiedBondGraph() { return mSimplifiedBondGraph; }
	
	virtual void setValue(float inFitness);
	virtual void setAdjustedValue(float inFitness);
	float getOriginalFitnessValue() const { return mOriginalFitness; }
	
private:
	std::vector<PACC::Matrix> mStateMatrices;
	GrowingBG::Handle mBondGraph;
	GrowingBG::Handle mSimplifiedBondGraph;
	
	float mOriginalFitness;
};

#endif
