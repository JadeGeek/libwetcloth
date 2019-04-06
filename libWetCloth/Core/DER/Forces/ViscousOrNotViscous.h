//
// This file is part of the libWetCloth open source project
//
// The code is licensed under the same terms as a Clear BSD License but further
// restricted to academic and non-commercial use (commercial licenses may be
// obtained by contacting the faculty of the Columbia Computer Graphics Group
// or Columbia Technology Ventures).
//
// Copyright 2012 Jean-Marie Aubry
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the disclaimer
// below) provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its contributors may be used
// to endorse or promote products derived from this software without specific
// prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
// LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.

#ifndef VISCOUS_OR_NOT_VISCOUS_H_
#define VISCOUS_OR_NOT_VISCOUS_H_

#include "../StrandForce.h"
#include "../StrandParameters.h"
// These classes are taken as template arguments for the internal forces,
// indicating whether we want the non-viscous or the viscous version.
// The forces call their ViscousT's static methods returning the appropriate
// stiffness and "rest shape" (the actual rest-shape for non-viscous or the
// shape at the beginning of time step for viscous).

class NonViscous
{
protected:
    NonViscous()
    {}

    virtual ~NonViscous()
    {}

public:
    static std::string getName()
    {
        return "";
    }

    static scalar bendingCoefficient( const StrandForce& strand, int vtx )
    {
        return strand.m_strandParams->bendingCoefficient( );
    }

    static Mat2 bendingMatrix( const StrandForce& strand, int vtx )
    {
        return strand.m_strandParams->bendingMatrix( vtx );
    }

    static const Vec2 kappaBar( const StrandForce& strand, int vtx )
    {
        return strand.m_restKappas[vtx];
    }

    static scalar kt( const StrandForce& strand, int vtx )
    {
        return strand.m_strandParams->getKt( vtx );
    }

    static scalar thetaBar( const StrandForce& strand, int vtx )
    {
        return strand.m_restTwists[vtx];
    }

    static scalar ks( const StrandForce& strand, int vtx )
    {
        return strand.m_strandParams->getKs( vtx );
    }

    static scalar ellBar( const StrandForce& strand, int vtx )
    {
        return strand.m_restLengths[vtx];
    }

    static const Vec2 bendingMultiplier( const StrandForce& strand, int vtx )
    {
        return strand.m_bending_multipliers.segment<2>( vtx * 2 );
    }

    static scalar stretchingMultiplier( const StrandForce& strand, int vtx )
    {
        return strand.m_stretching_multipliers( vtx );
    }

    static scalar twistingMultiplier( const StrandForce& strand, int vtx )
    {
        return strand.m_twisting_multipliers( vtx );
    }

    class NonDissipativeForce{};
};

class Viscous
{
protected:
    Viscous()
    {}

    virtual ~Viscous()
    {}

public:
    static std::string getName()
    {
        return "viscous ";
    }

    static scalar bendingCoefficient( const StrandForce& strand, int vtx )
    {
        return strand.m_strandParams->viscousBendingCoefficient( );
    }

    static Mat2 bendingMatrix( const StrandForce& strand, int vtx )
    {
        return strand.m_strandParams->viscousBendingMatrix( vtx );
    }

    static const Vec2 kappaBar( const StrandForce& strand, int vtx )
    {
        return strand.m_startState->m_kappas[vtx];
    }

    static scalar kt( const StrandForce& strand, int vtx )
    {
        return strand.m_strandParams->getViscousKt( vtx );
    }

    static scalar thetaBar( const StrandForce& strand, int vtx )
    {
        return strand.m_startState->m_twists[vtx];
    }

    static scalar ks( const StrandForce& strand, int vtx )
    {
        return strand.m_strandParams->getViscousKs( vtx );
    }

    static scalar ellBar( const StrandForce& strand, int vtx )
    {
        return strand.m_startState->m_lengths[vtx];
    }

    static const Vec2 bendingMultiplier( const StrandForce& strand, int vtx )
    {
        return strand.m_viscous_bending_multipliers.segment<2>( vtx * 2 );
    }

    static scalar stretchingMultiplier( const StrandForce& strand, int vtx )
    {
        return strand.m_viscous_stretching_multipliers( vtx );
    }

    static scalar twistingMultiplier( const StrandForce& strand, int vtx )
    {
        return strand.m_viscous_twisting_multipliers( vtx );
    }

    class DissipativeForce{};
};

#endif
