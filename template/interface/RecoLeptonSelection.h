#ifndef RecoLeptonSelection_H
#define RecoLeptonSelection_H

#include "format.h"
#include "DPHI.h"
#include "UseEIDRhoCorIsoR03.h"
#include "EffectiveAreaElectron.h"
#include "TLorentzVector.h"

void RecoLeptonSelection(EvtInfoBranches EvtInfo, LepInfoBranches LepInfo, int &NMuons, int *M_Index, int &NElectrons, int *E_Index,
        int &NLeptons, int *L_Index){

    double LLDR = 0.3;

    for(int nl=0;nl<LepInfo.Size;nl++){
        if((LepInfo.LeptonType[nl]==13)&&
                (fabs(LepInfo.Pt[nl])>20) &&
                //(fabs(LepInfo.Pt[nl])>30) &&
                //(fabs(LepInfo.Eta[nl])<2.4) &&
                (fabs(LepInfo.Eta[nl])<2.1) &&
                // Tight Muon
                (fabs(LepInfo.MuInnerTrackDxy_PV[nl])<0.2) &&
                (fabs(LepInfo.MuInnerTrackDz[nl])<0.5) &&
                (LepInfo.MuInnerTrackNHits[nl]>=11) &&
                (LepInfo.MuGlobalNormalizedChi2[nl]<10)&&
                (LepInfo.MuNPixelLayers[nl] >=1 ) &&
                (LepInfo.MuNChambersMatchesSegment[nl] >= 2) &&
                (LepInfo.MuNMuonhits[nl] >= 1) &&
                (LepInfo.MuNTrackLayersWMeasurement[nl] >= 6) &&
                ((LepInfo.ChargedHadronIsoR04[nl]+ max(0.,LepInfo.NeutralHadronIsoR04[nl]+LepInfo.PhotonIsoR04[nl]-0.5*LepInfo.sumPUPtR04[nl]))/LepInfo.Pt[nl]<0.12) &&
                //(LepInfo.IsoRhoCorrR04[nl]/LepInfo.Pt[nl]<0.12) &&
                (LepInfo.MuType[nl] == 46) 
          ) {
            M_Index[NMuons] = nl;
            NMuons++;
            L_Index[NLeptons] = nl;
            NLeptons++;
        }else if((LepInfo.LeptonType[nl]==11)&&
                (fabs(LepInfo.Pt[nl])>30) &&
                (((fabs(LepInfo.Eta[nl])<2.5)&&(fabs(LepInfo.Eta[nl])>=1.566)) || (fabs(LepInfo.Eta[nl])<1.444) ) &&
                //UseEIDRhoCorIsoR03(LepInfo,EvtInfo,nl,TIGHT)
                (LepInfo.ChargedHadronIsoR03[nl] + std::max( LepInfo.NeutralHadronIsoR03[nl] + LepInfo.PhotonIsoR03[nl] - std::max((double)EvtInfo.RhoPU[0], 0.0)*EffectiveAreaElectron(LepInfo.Eta[nl]),0.0) )/LepInfo.Pt[nl] < 0.1 &&
                LepInfo.NumberOfExpectedInnerHits[nl] <=0 &&
                !LepInfo.ElhasConv[nl] && // = passConversinoVeto
                LepInfo.ElTrackDxy_PV[nl] < 0.02 &&
                LepInfo.EgammaMVATrig[nl] > 0.9
                ){
            E_Index[NElectrons] = nl;
            NElectrons++;
            L_Index[NLeptons] = nl;
            NLeptons++;
        }
    }   

    // remove electron overlapping with muon
    const int n_index = NElectrons;
    int E_Index_temp[n_index]; 
    int NElectrons_temp = 0; 
    for(int fl=0;fl<n_index;fl++)   E_Index_temp[fl] = -1;
    for(int l1=0;l1<NElectrons;l1++){

        TLorentzVector electronTemp;
        electronTemp.SetPxPyPzE(LepInfo.Px[E_Index[l1]],
                LepInfo.Py[E_Index[l1]],
                LepInfo.Pz[E_Index[l1]],
                LepInfo.Energy[E_Index[l1]]);
        bool remove_electron = false;
        for(int l2=0;l2<NMuons;l2++){
            double dphi       = DPHI(LepInfo.Phi[M_Index[l2]],electronTemp.Phi());
            double deta       = fabs(LepInfo.Eta[M_Index[l2]]-electronTemp.Eta());
            double dR         = pow(dphi*dphi+deta*deta,0.5);
            if (dR<=LLDR) {
                remove_electron = true;
            }    
        }    
        if (remove_electron) continue;
        E_Index_temp[NElectrons_temp] = E_Index[l1];
        NElectrons_temp++;
    }    
    //if((NElectrons-NElectrons_temp)<0) std::cout<<"NElectrons-NElectrons_removed : "<<NElectrons-NElectrons_temp<<std::endl;
    NElectrons = NElectrons_temp;
    for(int fl=0;fl<n_index;fl++)   E_Index[fl] = E_Index_temp[fl];

    for(int fl=0;fl<NLeptons;fl++) L_Index[fl] = -1;
    NLeptons=NElectrons+NMuons;
    for(int fl=0;fl<NElectrons;fl++) L_Index[fl] = E_Index[fl];
    for(int fl=0;fl<NMuons;fl++) L_Index[fl+NElectrons] = M_Index[fl];
}

#endif
