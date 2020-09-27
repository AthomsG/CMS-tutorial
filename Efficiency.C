#include "src/compare_efficiency.cpp"
#include "src/DoFit.cpp"
#include "src/get_conditions.cpp"
#include "src/get_efficiency.cpp"
#include "src/make_hist.cpp"
#include "src/McYield.cpp"

void Efficiency()
{
    //We start by declaring the nature of our dataset. (Is the data real or simulated?)
    bool DataIsMC = FALSE;
    
    /*--------------------------------------------------------------------------------------
     The fitting method requires the segmentation of the quantity being studied
     into intervals of our desired size. (1)
     To achieve that we must create a string array with the intervals of each segment(bin).
    ----------------------------------------------------------------------------------------*/
    
    /*-----------------------------------INSERT CODE HERE-----------------------------------*/
    int bin_n = //Insert number of intervals(bins) here
    double* bin = new double[bin_n];
    
    string* conditions = get_conditions(bin_n, bins); // (1)
    
    //Now we must choose initial conditions in order to fit our data
    double *init_conditions = new double[4];
    /*-----------------------------------INSERT CODE HERE-----------------------------------*/
    init_conditions[0] = /*peak1*/;
    init_conditions[1] = /*peak2*/;
    init_conditions[2] = /*peak3*/;
    init_conditions[3] = /*sigma*/;
    
    double ** yields_n_errs = new double*[bin_n];
    
    for (int i = 0; i < bin_n; i++)
    {
        if (DataIsMC)
            yields_n_errs[i] = McYield(conditions[i]);
        else
            yields_n_errs[i] = doFit(conditions[i], "PassingProbeTrackerMuon", init_conditions);
            //doFit returns: [yield_all, yield_pass, err_all, err_pass]
    }
    
    TH1F *yield_ALL  = make_hist("ALL" , yields_n_errs, 0, bin_n, bins, DataIsMC);
    TH1F *yield_PASS = make_hist("PASS", yields_n_errs, 1, bin_n, bins, DataIsMC);
   
    //----------------------SAVING RESULTS TO .root--------------------//
    // useful if we require to change the fit on a specific set of bins
    TFile* EfficiencyFile = TFile::Open("Histograms.root","RECREATE");
    yield_ALL->SetDirectory(gDirectory);
    yield_PASS->SetDirectory(gDirectory);
    EfficiencyFile->Write();
    //-----------------------------------------------------------------//
    
    //If all of the fits seem correct we can proceed to generate the efficiency
    get_efficiency(yield_ALL, yield_PASS);
    
    //Once we've calculated the efficiency for both data sets, we can generate
    //a plot that combines both results
    
    string quantity = "";
    compare_efficiency(quantity);
}
