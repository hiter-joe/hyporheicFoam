/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2012 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include "chesurfaceBottomFvPatchScalarField.H"
#include "fvPatchFieldMapper.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::chesurfaceBottomFvPatchScalarField
::chesurfaceBottomFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
:
    mixedFvPatchScalarField(p, iF),
    YiFromSub_(p.size(), 0.0),
    phiName_("phi")
{
    this->refValue() = 0.0;
    this->refGrad() = 0.0;
    this->valueFraction() = 0.0;
}


Foam::chesurfaceBottomFvPatchScalarField
::chesurfaceBottomFvPatchScalarField
(
    const chesurfaceBottomFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    mixedFvPatchScalarField(ptf, p, iF, mapper),
    YiFromSub_(ptf.YiFromSub_, mapper),
    phiName_(ptf.phiName_)
{}


Foam::chesurfaceBottomFvPatchScalarField
::chesurfaceBottomFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
:
    mixedFvPatchScalarField(p, iF),
    YiFromSub_("YiFromSub", dict, p.size()),
    phiName_(dict.lookupOrDefault<word>("phi", "phi"))
{
    this->refValue() = 0.0;

    if (dict.found("value"))
    {
        fvPatchScalarField::operator=
        (
            scalarField("value", dict, p.size())
        );
    }
    else
    {
        fvPatchScalarField::operator=(this->patchInternalField());
    }

    this->refGrad() = 0.0;
    this->valueFraction() = 0.0;
}


Foam::chesurfaceBottomFvPatchScalarField
    ::chesurfaceBottomFvPatchScalarField
(
    const chesurfaceBottomFvPatchScalarField& ptf
)
:
    mixedFvPatchScalarField(ptf),
    YiFromSub_(ptf.YiFromSub_),
    phiName_(ptf.phiName_)
{}


Foam::chesurfaceBottomFvPatchScalarField
    ::chesurfaceBottomFvPatchScalarField
(
    const chesurfaceBottomFvPatchScalarField& ptf,
    const DimensionedField<scalar, volMesh>& iF
)
:
    mixedFvPatchScalarField(ptf, iF),
    YiFromSub_(ptf.YiFromSub_),
    phiName_(ptf.phiName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::chesurfaceBottomFvPatchScalarField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    //fluid flux on this patch
    const fvsPatchField<scalar>& phip =
        patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

    forAll(YiFromSub_, facei)
    {
        if(phip[facei] >= 0.0) //flux surface -> subsurface: zeroGradient
        {
           this->refGrad()[facei] = 0.0;
           this->valueFraction()[facei] = 0.0;
        }
        else                   //flux surface <- subsurface: fixedValue
        {

           this->refValue()[facei] = YiFromSub_[facei];
           this->valueFraction()[facei] = 1.0;
        }
    }

    mixedFvPatchScalarField::updateCoeffs();
}


void Foam::chesurfaceBottomFvPatchScalarField::write(Ostream& os) const
{
    mixedFvPatchField<scalar>::write(os);
    YiFromSub_.writeEntry("YiFromSub",os);
    if (phiName_ != "phi")
    {
        os.writeKeyword("phi") << phiName_ << token::END_STATEMENT << nl;
    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchScalarField,
        chesurfaceBottomFvPatchScalarField
    );
}

// ************************************************************************* //
