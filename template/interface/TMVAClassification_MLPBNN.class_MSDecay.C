// Class: ReadMLPBNN
// Automatically generated by MethodBase::MakeClass
//

/* configuration options =====================================================

#GEN -*-*-*-*-*-*-*-*-*-*-*- general info -*-*-*-*-*-*-*-*-*-*-*-

Method         : MLP::MLPBNN
TMVA Release   : 4.1.3         [262403]
ROOT Release   : 5.34/03       [336387]
Creator        : yeng-mingtzeng
Date           : Mon Sep 15 19:14:58 2014
Host           : Darwin macphsft02.cern.ch 10.8.0 Darwin Kernel Version 10.8.0: Tue Jun 7 16:33:36 PDT 2011; root:xnu-1504.15.3~1/RELEASE_I386 i386
Dir            : /Volumes/Data_HD/panda/files_IBM/ubuntu/CMS/WORKSPACE/stock/STOCK/v_31122009/ana/TMVA/TMVA-v4.2.0/test
Training events: 57251
Analysis type  : [Classification]


#OPT -*-*-*-*-*-*-*-*-*-*-*-*- options -*-*-*-*-*-*-*-*-*-*-*-*-

# Set by User:
NCycles: "600" [Number of training cycles]
HiddenLayers: "N+5" [Specification of hidden layer architecture]
NeuronType: "tanh" [Neuron activation function type]
V: "False" [Verbose output (short form of "VerbosityLevel" below - overrides the latter one)]
VarTransform: "N" [List of variable transformations performed before training, e.g., "D_Background,P_Signal,G,N_AllClasses" for: "Decorrelation, PCA-transformation, Gaussianisation, Normalisation, each for the given class of events ('AllClasses' denotes all events of all classes, if no class indication is given, 'All' is assumed)"]
H: "True" [Print method-specific help message]
TrainingMethod: "BFGS" [Train with Back-Propagation (BP), BFGS Algorithm (BFGS), or Genetic Algorithm (GA - slower and worse)]
TestRate: "5" [Test for overtraining performed at each #th epochs]
UseRegulator: "True" [Use regulator to avoid over-training]
# Default:
RandomSeed: "1" [Random seed for initial synapse weights (0 means unique seed for each run; default value '1')]
EstimatorType: "MSE" [MSE (Mean Square Estimator) for Gaussian Likelihood or CE(Cross-Entropy) for Bernoulli Likelihood]
NeuronInputType: "sum" [Neuron input function type]
VerbosityLevel: "Default" [Verbosity level]
CreateMVAPdfs: "False" [Create PDFs for classifier outputs (signal and background)]
IgnoreNegWeightsInTraining: "False" [Events with negative weights are ignored in the training (but are included for testing and performance evaluation)]
LearningRate: "2.000000e-02" [ANN learning rate parameter]
DecayRate: "1.000000e-02" [Decay rate for learning parameter]
EpochMonitoring: "False" [Provide epoch-wise monitoring plots according to TestRate (caution: causes big ROOT output file!)]
Sampling: "1.000000e+00" [Only 'Sampling' (randomly selected) events are trained each epoch]
SamplingEpoch: "1.000000e+00" [Sampling is used for the first 'SamplingEpoch' epochs, afterwards, all events are taken for training]
SamplingImportance: "1.000000e+00" [ The sampling weights of events in epochs which successful (worse estimator than before) are multiplied with SamplingImportance, else they are divided.]
SamplingTraining: "True" [The training sample is sampled]
SamplingTesting: "False" [The testing sample is sampled]
ResetStep: "50" [How often BFGS should reset history]
Tau: "3.000000e+00" [LineSearch "size step"]
BPMode: "sequential" [Back-propagation learning mode: sequential or batch]
BatchSize: "-1" [Batch size: number of events/batch, only set if in Batch Mode, -1 for BatchSize=number_of_events]
ConvergenceImprove: "1.000000e-30" [Minimum improvement which counts as improvement (<0 means automatic convergence check is turned off)]
ConvergenceTests: "-1" [Number of steps (without improvement) required for convergence (<0 means automatic convergence check is turned off)]
UpdateLimit: "10000" [Maximum times of regulator update]
CalculateErrors: "False" [Calculates inverse Hessian matrix at the end of the training to be able to calculate the uncertainties of an MVA value]
WeightRange: "1.000000e+00" [Take the events for the estimator calculations from small deviations from the desired value to large deviations only over the weight range]
##


#VAR -*-*-*-*-*-*-*-*-*-*-*-* variables *-*-*-*-*-*-*-*-*-*-*-*-

NVar 6
CHF                           CHF                           CHF                           CHF                           units                             'D'    [0.00165944092441,0.989949703217]
NHF                           NHF                           NHF                           NHF                           units                             'D'    [0.000950582441874,0.949002444744]
CHFandNHF                     CHFandNHF                     CHFandNHF                     CHFandNHF                     units                             'D'    [0.00958310160786,1.00000011921]
CHForder                      CHForder                      CHForder                      CHForder                      units                             'I'    [0,15]
NHForder                      NHForder                      NHForder                      NHForder                      units                             'I'    [0,15]
CHFandNHForder                CHFandNHForder                CHFandNHForder                CHFandNHForder                units                             'I'    [0,15]
NSpec 0


============================================================================ */

#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#ifndef IClassifierReader__def
#define IClassifierReader__def

class IClassifierReader {

 public:

   // constructor
   IClassifierReader() : fStatusIsClean( true ) {}
   virtual ~IClassifierReader() {}

   // return classifier response
   virtual double GetMvaValue( const std::vector<double>& inputValues ) const = 0;

   // returns classifier status
   bool IsStatusClean() const { return fStatusIsClean; }

 protected:

   bool fStatusIsClean;
};

#endif

class ReadMLPBNN : public IClassifierReader {

 public:

   // constructor
   ReadMLPBNN( std::vector<std::string>& theInputVars ) 
      : IClassifierReader(),
        fClassName( "ReadMLPBNN" ),
        fNvars( 6 ),
        fIsNormalised( false )
   {      
      // the training input variables
      const char* inputVars[] = { "CHF", "NHF", "CHFandNHF", "CHForder", "NHForder", "CHFandNHForder" };

      // sanity checks
      if (theInputVars.size() <= 0) {
         std::cout << "Problem in class \"" << fClassName << "\": empty input vector" << std::endl;
         fStatusIsClean = false;
      }

      if (theInputVars.size() != fNvars) {
         std::cout << "Problem in class \"" << fClassName << "\": mismatch in number of input values: "
                   << theInputVars.size() << " != " << fNvars << std::endl;
         fStatusIsClean = false;
      }

      // validate input variables
      for (size_t ivar = 0; ivar < theInputVars.size(); ivar++) {
         if (theInputVars[ivar] != inputVars[ivar]) {
            std::cout << "Problem in class \"" << fClassName << "\": mismatch in input variable names" << std::endl
                      << " for variable [" << ivar << "]: " << theInputVars[ivar].c_str() << " != " << inputVars[ivar] << std::endl;
            fStatusIsClean = false;
         }
      }

      // initialize min and max vectors (for normalisation)
      fVmin[0] = -1;
      fVmax[0] = 0.99999988079071;
      fVmin[1] = -1;
      fVmax[1] = 0.99999988079071;
      fVmin[2] = -1;
      fVmax[2] = 1;
      fVmin[3] = -1;
      fVmax[3] = 1;
      fVmin[4] = -1;
      fVmax[4] = 1;
      fVmin[5] = -1;
      fVmax[5] = 1;

      // initialize input variable types
      fType[0] = 'D';
      fType[1] = 'D';
      fType[2] = 'D';
      fType[3] = 'I';
      fType[4] = 'I';
      fType[5] = 'I';

      // initialize constants
      Initialize();

      // initialize transformation
      InitTransform();
   }

   // destructor
   virtual ~ReadMLPBNN() {
      Clear(); // method-specific
   }

   // the classifier response
   // "inputValues" is a vector of input values in the same order as the 
   // variables given to the constructor
   double GetMvaValue( const std::vector<double>& inputValues ) const;

 private:

   // method-specific destructor
   void Clear();

   // input variable transformation

   double fMin_1[3][6];
   double fMax_1[3][6];
   void InitTransform_1();
   void Transform_1( std::vector<double> & iv, int sigOrBgd ) const;
   void InitTransform();
   void Transform( std::vector<double> & iv, int sigOrBgd ) const;

   // common member variables
   const char* fClassName;

   const size_t fNvars;
   size_t GetNvar()           const { return fNvars; }
   char   GetType( int ivar ) const { return fType[ivar]; }

   // normalisation of input variables
   const bool fIsNormalised;
   bool IsNormalised() const { return fIsNormalised; }
   double fVmin[6];
   double fVmax[6];
   double NormVariable( double x, double xmin, double xmax ) const {
      // normalise to output range: [-1, 1]
      return 2*(x - xmin)/(xmax - xmin) - 1.0;
   }

   // type of input variable: 'F' or 'I'
   char   fType[6];

   // initialize internal variables
   void Initialize();
   double GetMvaValue__( const std::vector<double>& inputValues ) const;

   // private members (method specific)

   double ActivationFnc(double x) const;
   double OutputActivationFnc(double x) const;

   int fLayers;
   int fLayerSize[3];
   double fWeightMatrix0to1[12][7];   // weight matrix from layer 0 to 1
   double fWeightMatrix1to2[1][12];   // weight matrix from layer 1 to 2

   double * fWeights[3];
};

inline void ReadMLPBNN::Initialize()
{
   // build network structure
   fLayers = 3;
   fLayerSize[0] = 7; fWeights[0] = new double[7]; 
   fLayerSize[1] = 12; fWeights[1] = new double[12]; 
   fLayerSize[2] = 1; fWeights[2] = new double[1]; 
   // weight matrix from layer 0 to 1
   fWeightMatrix0to1[0][0] = 0.055362062033846;
   fWeightMatrix0to1[1][0] = 0.884733596435151;
   fWeightMatrix0to1[2][0] = 0.695909534355229;
   fWeightMatrix0to1[3][0] = 1.64595769041622;
   fWeightMatrix0to1[4][0] = -1.98809982305172;
   fWeightMatrix0to1[5][0] = 0.00576632029319;
   fWeightMatrix0to1[6][0] = 0.803276706330803;
   fWeightMatrix0to1[7][0] = 1.11391580021455;
   fWeightMatrix0to1[8][0] = -0.525579373882082;
   fWeightMatrix0to1[9][0] = -1.28694633651627;
   fWeightMatrix0to1[10][0] = -1.74676198045133;
   fWeightMatrix0to1[0][1] = -1.27635605625257;
   fWeightMatrix0to1[1][1] = -0.332001012332091;
   fWeightMatrix0to1[2][1] = 0.122987433029738;
   fWeightMatrix0to1[3][1] = -0.327732312512075;
   fWeightMatrix0to1[4][1] = 0.90312592911459;
   fWeightMatrix0to1[5][1] = -1.84539372564427;
   fWeightMatrix0to1[6][1] = 0.491457740684454;
   fWeightMatrix0to1[7][1] = 1.52763890882647;
   fWeightMatrix0to1[8][1] = 1.54641875952444;
   fWeightMatrix0to1[9][1] = 0.228486730491834;
   fWeightMatrix0to1[10][1] = 0.154367708365493;
   fWeightMatrix0to1[0][2] = 0.389637290072623;
   fWeightMatrix0to1[1][2] = -0.625860256661398;
   fWeightMatrix0to1[2][2] = -0.798097102717441;
   fWeightMatrix0to1[3][2] = 0.102951716572647;
   fWeightMatrix0to1[4][2] = 1.48900993652436;
   fWeightMatrix0to1[5][2] = -1.35366995626289;
   fWeightMatrix0to1[6][2] = -2.03290395172133;
   fWeightMatrix0to1[7][2] = 0.780954119296179;
   fWeightMatrix0to1[8][2] = 2.09687222962429;
   fWeightMatrix0to1[9][2] = 2.48544481934302;
   fWeightMatrix0to1[10][2] = -1.14840557395555;
   fWeightMatrix0to1[0][3] = 0.0680554215788067;
   fWeightMatrix0to1[1][3] = 0.207747910030295;
   fWeightMatrix0to1[2][3] = -0.441914386251338;
   fWeightMatrix0to1[3][3] = -0.577650168786895;
   fWeightMatrix0to1[4][3] = 1.11063805256393;
   fWeightMatrix0to1[5][3] = 0.537206846684884;
   fWeightMatrix0to1[6][3] = -0.067698121867533;
   fWeightMatrix0to1[7][3] = 0.712061021899042;
   fWeightMatrix0to1[8][3] = 0.65583501137694;
   fWeightMatrix0to1[9][3] = 0.523565300581064;
   fWeightMatrix0to1[10][3] = 0.111188995895451;
   fWeightMatrix0to1[0][4] = -0.174931814331484;
   fWeightMatrix0to1[1][4] = -0.37105508125512;
   fWeightMatrix0to1[2][4] = 0.508864456946569;
   fWeightMatrix0to1[3][4] = 0.133958648474669;
   fWeightMatrix0to1[4][4] = 1.30512754628975;
   fWeightMatrix0to1[5][4] = -0.00582917508948725;
   fWeightMatrix0to1[6][4] = 0.740091021803091;
   fWeightMatrix0to1[7][4] = 0.0550048489814713;
   fWeightMatrix0to1[8][4] = -0.94826544039857;
   fWeightMatrix0to1[9][4] = 0.751221840745536;
   fWeightMatrix0to1[10][4] = -0.370142423247124;
   fWeightMatrix0to1[0][5] = -0.387780152880532;
   fWeightMatrix0to1[1][5] = -1.12789716839104;
   fWeightMatrix0to1[2][5] = -1.52221215086764;
   fWeightMatrix0to1[3][5] = 1.30016537870406;
   fWeightMatrix0to1[4][5] = 0.381132063889284;
   fWeightMatrix0to1[5][5] = -1.12219945521807;
   fWeightMatrix0to1[6][5] = 0.0815375581477532;
   fWeightMatrix0to1[7][5] = -0.164436655317468;
   fWeightMatrix0to1[8][5] = 0.734553823296552;
   fWeightMatrix0to1[9][5] = 1.32567995814357;
   fWeightMatrix0to1[10][5] = -0.56793088946325;
   fWeightMatrix0to1[0][6] = 0.340040905878596;
   fWeightMatrix0to1[1][6] = -1.70314454675187;
   fWeightMatrix0to1[2][6] = 0.648519577002128;
   fWeightMatrix0to1[3][6] = -0.722918715201984;
   fWeightMatrix0to1[4][6] = -0.815115338359783;
   fWeightMatrix0to1[5][6] = -1.67878449004008;
   fWeightMatrix0to1[6][6] = -0.0680159451503707;
   fWeightMatrix0to1[7][6] = 1.13345589659374;
   fWeightMatrix0to1[8][6] = 1.65247334264592;
   fWeightMatrix0to1[9][6] = 0.424870426603663;
   fWeightMatrix0to1[10][6] = -3.3673278316927;
   // weight matrix from layer 1 to 2
   fWeightMatrix1to2[0][0] = 0.0479196636576222;
   fWeightMatrix1to2[0][1] = 0.198842985939799;
   fWeightMatrix1to2[0][2] = -0.0268892592287356;
   fWeightMatrix1to2[0][3] = 0.0162650000360676;
   fWeightMatrix1to2[0][4] = 0.0333098921746541;
   fWeightMatrix1to2[0][5] = 0.193016027277507;
   fWeightMatrix1to2[0][6] = -0.369882489644105;
   fWeightMatrix1to2[0][7] = -0.145624498515663;
   fWeightMatrix1to2[0][8] = -0.107385064063972;
   fWeightMatrix1to2[0][9] = 0.103703500328232;
   fWeightMatrix1to2[0][10] = -0.264188673246181;
   fWeightMatrix1to2[0][11] = -0.111151197141934;
}

inline double ReadMLPBNN::GetMvaValue__( const std::vector<double>& inputValues ) const
{
   if (inputValues.size() != (unsigned int)fLayerSize[0]-1) {
      std::cout << "Input vector needs to be of size " << fLayerSize[0]-1 << std::endl;
      return 0;
   }

   for (int l=0; l<fLayers; l++)
      for (int i=0; i<fLayerSize[l]; i++) fWeights[l][i]=0;

   for (int l=0; l<fLayers-1; l++)
      fWeights[l][fLayerSize[l]-1]=1;

   for (int i=0; i<fLayerSize[0]-1; i++)
      fWeights[0][i]=inputValues[i];

   // layer 0 to 1
   for (int o=0; o<fLayerSize[1]-1; o++) {
      for (int i=0; i<fLayerSize[0]; i++) {
         double inputVal = fWeightMatrix0to1[o][i] * fWeights[0][i];
         fWeights[1][o] += inputVal;
      }
      fWeights[1][o] = ActivationFnc(fWeights[1][o]);
   }
   // layer 1 to 2
   for (int o=0; o<fLayerSize[2]; o++) {
      for (int i=0; i<fLayerSize[1]; i++) {
         double inputVal = fWeightMatrix1to2[o][i] * fWeights[1][i];
         fWeights[2][o] += inputVal;
      }
      fWeights[2][o] = OutputActivationFnc(fWeights[2][o]);
   }

   return fWeights[2][0];
}

double ReadMLPBNN::ActivationFnc(double x) const {
   // hyperbolic tan
   return tanh(x);
}
double ReadMLPBNN::OutputActivationFnc(double x) const {
   // identity
   return x;
}
   
// Clean up
inline void ReadMLPBNN::Clear() 
{
   // nothing to clear
}
   inline double ReadMLPBNN::GetMvaValue( const std::vector<double>& inputValues ) const
   {
      // classifier response value
      double retval = 0;

      // classifier response, sanity check first
      if (!IsStatusClean()) {
         std::cout << "Problem in class \"" << fClassName << "\": cannot return classifier response"
                   << " because status is dirty" << std::endl;
         retval = 0;
      }
      else {
         if (IsNormalised()) {
            // normalise variables
            std::vector<double> iV;
            int ivar = 0;
            for (std::vector<double>::const_iterator varIt = inputValues.begin();
                 varIt != inputValues.end(); varIt++, ivar++) {
               iV.push_back(NormVariable( *varIt, fVmin[ivar], fVmax[ivar] ));
            }
            Transform( iV, -1 );
            retval = GetMvaValue__( iV );
         }
         else {
            std::vector<double> iV;
            int ivar = 0;
            for (std::vector<double>::const_iterator varIt = inputValues.begin();
                 varIt != inputValues.end(); varIt++, ivar++) {
               iV.push_back(*varIt);
            }
            Transform( iV, -1 );
            retval = GetMvaValue__( iV );
         }
      }

      return retval;
   }

//_______________________________________________________________________
inline void ReadMLPBNN::InitTransform_1()
{
   // Normalization transformation, initialisation
   fMin_1[0][0] = 0.00284713879228;
   fMax_1[0][0] = 0.974948406219;
   fMin_1[1][0] = 0.00165944092441;
   fMax_1[1][0] = 0.989949703217;
   fMin_1[2][0] = 0.00165944092441;
   fMax_1[2][0] = 0.989949703217;
   fMin_1[0][1] = 0.000950582441874;
   fMax_1[0][1] = 0.843511819839;
   fMin_1[1][1] = 0.00103764072992;
   fMax_1[1][1] = 0.949002444744;
   fMin_1[2][1] = 0.000950582441874;
   fMax_1[2][1] = 0.949002444744;
   fMin_1[0][2] = 0.0416324213147;
   fMax_1[0][2] = 0.993237495422;
   fMin_1[1][2] = 0.00958310160786;
   fMax_1[1][2] = 1.00000011921;
   fMin_1[2][2] = 0.00958310160786;
   fMax_1[2][2] = 1.00000011921;
   fMin_1[0][3] = 0;
   fMax_1[0][3] = 14;
   fMin_1[1][3] = 0;
   fMax_1[1][3] = 15;
   fMin_1[2][3] = 0;
   fMax_1[2][3] = 15;
   fMin_1[0][4] = 0;
   fMax_1[0][4] = 14;
   fMin_1[1][4] = 0;
   fMax_1[1][4] = 15;
   fMin_1[2][4] = 0;
   fMax_1[2][4] = 15;
   fMin_1[0][5] = 0;
   fMax_1[0][5] = 14;
   fMin_1[1][5] = 0;
   fMax_1[1][5] = 15;
   fMin_1[2][5] = 0;
   fMax_1[2][5] = 15;
}

//_______________________________________________________________________
inline void ReadMLPBNN::Transform_1( std::vector<double>& iv, int cls) const
{
   // Normalization transformation
   if (cls < 0 || cls > 2) {
   if (2 > 1 ) cls = 2;
      else cls = 2;
   }
   const int nVar = 6;

   // get indices of used variables

   // define the indices of the variables which are transformed by this transformation
   std::vector<int> indicesGet;
   std::vector<int> indicesPut;

   indicesGet.push_back( 0);
   indicesGet.push_back( 1);
   indicesGet.push_back( 2);
   indicesGet.push_back( 3);
   indicesGet.push_back( 4);
   indicesGet.push_back( 5);
   indicesPut.push_back( 0);
   indicesPut.push_back( 1);
   indicesPut.push_back( 2);
   indicesPut.push_back( 3);
   indicesPut.push_back( 4);
   indicesPut.push_back( 5);

   std::vector<double> dv(nVar);
   for (int ivar=0; ivar<nVar; ivar++) dv[ivar] = iv[indicesGet.at(ivar)];
   for (int ivar=0;ivar<6;ivar++) {
      double offset = fMin_1[cls][ivar];
      double scale  = 1.0/(fMax_1[cls][ivar]-fMin_1[cls][ivar]);
      iv[indicesPut.at(ivar)] = (dv[ivar]-offset)*scale * 2 - 1;
   }
}

//_______________________________________________________________________
inline void ReadMLPBNN::InitTransform()
{
   InitTransform_1();
}

//_______________________________________________________________________
inline void ReadMLPBNN::Transform( std::vector<double>& iv, int sigOrBgd ) const
{
   Transform_1( iv, sigOrBgd );
}
