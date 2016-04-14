////////////////////////////////////////////////////////////////////////
// \file PhotonVisibilityService.h
//
// \brief Service to report opdet visibility to different points in
//         the system
//
// \author bjpjones@mit.edu
//
////////////////////////////////////////////////////////////////////////
#ifndef PHOTONVISIBILITYSERVICE_H
#define PHOTONVISIBILITYSERVICE_H


#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "larsim/PhotonPropagation/PhotonLibrary.h"

///General LArSoft Utilities
namespace phot{
  
  class PhotonVisibilityService {
  public:
    
    PhotonVisibilityService(fhicl::ParameterSet const& pset, art::ActivityRegistry& reg);
    
    void reconfigure(fhicl::ParameterSet const& p);
    
    double GetQuenchingFactor(double dQdx) const;
    
    static double DistanceToOpDet(          double const* xyz, unsigned int OpDet );
    static double SolidAngleFactor(         double const* xyz, unsigned int OpDet );
    float GetVisibility(                    double const* xyz, unsigned int OpChannel ) const;         

    float const* GetAllVisibilities( double const* xyz ) const;
    
    void LoadLibrary() const;
    void StoreLibrary();
    
    
    void StoreLightProd(    int  VoxID,  double  N );
    void RetrieveLightProd( int& VoxID,  double& N ) const;
    
    void SetLibraryEntry(   int VoxID, int OpChannel, float N);
    float GetLibraryEntry( int VoxID, int OpChannel) const;
    float const* GetLibraryEntries( int VoxID ) const;

    
    bool IsBuildJob() const { return fLibraryBuildJob; }
    bool UseParameterization() const {return fParameterization;}

    sim::PhotonVoxelDef GetVoxelDef() const {return fVoxelDef; }
    size_t NOpChannels() const;
    
  private:
    
    int    fCurrentVoxel;
    double fCurrentValue;
    
    float  fXmin, fXmax;
    float  fYmin, fYmax;
    float  fZmin, fZmax;
    int    fNx, fNy, fNz;

    bool fUseCryoBoundary;
    
    bool                 fLibraryBuildJob;
    bool                 fDoNotLoadLibrary;
    bool                 fParameterization;
    std::string          fLibraryFile;      
    mutable PhotonLibrary* fTheLibrary;
    sim::PhotonVoxelDef  fVoxelDef;
    
    
  }; // class PhotonVisibilityService
} //namespace utils
DECLARE_ART_SERVICE(phot::PhotonVisibilityService, LEGACY)
#endif // UTIL_DETECTOR_PROPERTIES_H
