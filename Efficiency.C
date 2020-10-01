#include "src/compare_efficiency.C"
#include "src/DoFit.cpp"
#include "src/get_conditions.cpp"
#include "src/get_efficiency.cpp"
#include "src/change_bin.cpp"
#include "src/make_hist.cpp"
#include "src/McYield.cpp"

void Efficiency()
{
    //We start by declaring the nature of our dataset. (Is the data real or simulated?)
    bool DataIsMC   = false;
    //Which Muon Id do you want to study?
    string MuonId   = "PassingProbeTrackingMuon";
    //Which quantity do you want to use?
    string quantity = "Pt"; //Pt, Eta or Phi
    
    /*-----------------------------------I N S E R T    C O D E    H E R E-----------------------------------*/
    double bins[] =  ...;
    int bin_n     =  ...;
     /*------------------------------------------------------------------------------------------------------*/
    
    
    //Now we must choose initial conditions in order to fit our data
    double *init_conditions = new double[4];
    /*-----------------------------------I N S E R T    C O D E    H E R E-----------------------------------*/
    init_conditions[0] = /*peak1*/;
    init_conditions[1] = /*peak2*/;
    init_conditions[2] = /*peak3*/;
    init_conditions[3] = /*sigma*/;
    /*------------------------------------------------------------------------------------------------------*/
    
    
    string* conditions = get_conditions(bin_n, bins, "ProbeMuon_" + quantity);
    double ** yields_n_errs = new double*[bin_n];
    
    for (int i = 0; i < bin_n; i++)
    {
        if (DataIsMC)
            yields_n_errs[i] = McYield(conditions[i], quantity);
        else
            yields_n_errs[i] = doFit(conditions[i], MuonId, quantity, init_conditions);
            //doFit returns: [yield_all, yield_pass, err_all, err_pass]
    }
    
    TH1F *yield_ALL  = make_hist("ALL" , yields_n_errs, 0, bin_n, bins, DataIsMC);
    TH1F *yield_PASS = make_hist("PASS", yields_n_errs, 1, bin_n, bins, DataIsMC);
    
    //----------------------SAVING RESULTS TO Histograms.root--------------------//
    //useful if we require to change the fit on a specific set of bins
    TFile* EfficiencyFile = TFile::Open("Histograms.root","RECREATE");
    yield_ALL->SetDirectory(gDirectory);
    yield_PASS->SetDirectory(gDirectory);
    EfficiencyFile->Write();
    //-----------------------------------------------------------------//
    
    //If all of the fits seem correct we can proceed to generate the efficiency
    get_efficiency(yield_ALL, yield_PASS, quantity, DataIsMC);
     
    //In case you want to change the fit on a specific, comment the loop and "result saving" code and uncomment the following function
    //change_bin(/*bin number you want to redo*/, /*condition (you can copy the title from the generated fit .pdf)*/, MuonId, quantity, DataIsMC, init_conditions);
    //bins start on 1
    
    //Once we've calculated the efficiency for both data sets, we can generate
    //a plot that combines both results
    compare_efficiency(quantity, "Efficiency Result/" + quantity + "/Efficiency_MC.root", "Efficiency Result/" + quantity + "/Efficiency_Run2011.root");
}
