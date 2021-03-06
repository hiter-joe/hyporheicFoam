
    //the bottom patch of the flow (surface) domain
    label surfaceBottomPatchID = meshSource.boundaryMesh().findPatchID("bottom");

    //the top patch of the sediment (subsurface) domain
    label subSurfaceTopPatchID = meshTarget.boundaryMesh().findPatchID("top");

    if(subSurfaceTopPatchID == -1 || surfaceBottomPatchID == -1)
    {
        FatalErrorIn(args.executable())
            << "Didn't find the patch named top in the subsurface domain"
            << " or the patch named bottom in the surface doamin"
            << abort(FatalError);
    }

    const primitivePatch& surfaceBottomPatch = 
                      meshSource.boundary()[surfaceBottomPatchID].patch();

    const primitivePatch& subSurfaceTopPatch =
                      meshTarget.boundary()[subSurfaceTopPatchID].patch();

    //- Patch to patch interpolator
    //from surface to subsurface
    PatchToPatchInterpolation<primitivePatch,primitivePatch> surfaceToBedInterpolate
    (
          surfaceBottomPatch, //fromPatch
          subSurfaceTopPatch  //toPatch
    );

    //from subsurface to surface
    PatchToPatchInterpolation<primitivePatch, primitivePatch> bedToSurfaceInterpolate
    (
          subSurfaceTopPatch, //fromPatch
          surfaceBottomPatch  //toPatch
    );

