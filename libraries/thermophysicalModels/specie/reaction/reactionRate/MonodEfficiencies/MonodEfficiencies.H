/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2017 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::MonodEfficiencies

Description
    Monod-type efficiencies: these coefficients are the half-saturation constants

SourceFiles
    MonodEfficienciesI.H

\*---------------------------------------------------------------------------*/

#ifndef MonodEfficiencies_H
#define MonodEfficiencies_H

#include "scalarList.H"
#include "speciesTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

class MonodEfficiencies;
Ostream& operator<<(Ostream&, const MonodEfficiencies&);


/*---------------------------------------------------------------------------*\
                  Class MonodEfficiencies Declaration
\*---------------------------------------------------------------------------*/

class MonodEfficiencies
:
    public scalarList
{
    // Private data

        const speciesTable& species_;

        //check the sanity of the Monod coefficients (>=0)
        inline void checkCoeff() const;

public:

    // Constructors

        //- Construct from components
        inline MonodEfficiencies
        (
            const speciesTable& species,
            const scalarList& efficiencies
        );

        //- Construct from dictionary
        inline MonodEfficiencies
        (
            const speciesTable& species,
            const dictionary& dict
        );


    // Member functions

        //- Calculate and return M as a fuction the concentration of the species
        inline scalar M(const scalarList& c) const;

        //- Write to stream
        inline void write(Ostream& os) const;



    // Ostream Operator

        friend Ostream& operator<<(Ostream&, const MonodEfficiencies&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "MonodEfficienciesI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
