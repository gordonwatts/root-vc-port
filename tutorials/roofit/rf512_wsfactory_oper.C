/////////////////////////////////////////////////////////////////////////
//
// 'ORGANIZATION AND SIMULTANEOUS FITS' RooFit tutorial macro #512
// 
//  Illustration of operator expressions and expression-based
//  basic p.d.f.s in the workspace factory syntax
//
// 04/2009 - Wouter Verkerke 
//
/////////////////////////////////////////////////////////////////////////

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
using namespace RooFit ;


void rf512_wsfactory_oper()
{
  RooWorkspace* w = new RooWorkspace("w") ;

  // You can define typedefs for even shorter construction semantics
  w->factory("$Typedef(Gaussian,Gaus)") ;
  w->factory("$Typedef(Chebychev,Cheby)") ;


  // O p e r a t o r   p . d . f .   e x a m p l e s 
  // ------------------------------------------------

  // PDF addition is done with SUM (coef1*pdf1,pdf2)
  w->factory("SUM::summodel( f[0,1]*Gaussian::gx(x[-10,10],m[0],1.0), Chebychev::ch(x,{0.1,0.2,-0.3}) )") ;
  

  // Extended PDF addition is done with SUM (yield1*pdf1,yield2*pdf2)
  w->factory("SUM::extsummodel( Nsig[0,1000]*gx, Nbkg[0,1000]*ch )") ;
  

  // PDF multiplication is done with PROD ( pdf1, pdf2 ) 
  w->factory("PROD::gxz( gx, Gaussian::gz(z[-10,10],0,1) )") ;


  // Conditional p.d.f multiplication is done with PROD ( pdf1|obs, pdf2 )
  w->factory("Gaussian::gy( y[-10,10], x, 1.0 )") ;
  w->factory("PROD::gxycond( gy|x, gx )") ;


  // Convolution (numeric/ fft) is done with NCONV/FCONV (obs,pdf1,pdf2)
  w->factory("FCONV::lxg( x, Gaussian::g(x,mg[0],1), Landau::lc(x,0,1) )") ;


  // Simultaneous p.d.f.s are constructed with SIMUL( index, state1=pdf1, state2=pdf2,...)
  w->factory("SIMUL::smodel( c[A=0,B=1], A=Gaussian::gs(x,m,s[1]), B=Landau::ls(x,0,1) )") ; 




  // O p e r a t o r   f u n c t i o n   e x a m p l e s 
  // ---------------------------------------------------
  
  // Function multiplication is done with prod (func1, func2,...)
  w->factory("prod::uv(u[10],v[10])") ;


  // Function addition is done with sum(func1,func2)
  w->factory("sum::uv2(u,v)") ;



  // I n t e r p r e t e d   a n d   c o m p i l e d   e x p r e s s i o n   b a s e d   p . d . f . s .
  // ---------------------------------------------------------------------------------------------------

  // Create a RooGenericPdf interpreted p.d.f. You can use single quotes to pass the expression string argument
  w->factory("EXPR::G('x*x+1',x)") ;

  // Create a custom compiled p.d.f similar to the above interpreted p.d.f.
  // The code required to make this p.d.f. is automatically embedded in the workspace
  w->factory("CEXPR::GC('x*x+a',{x,a[1]})") ;


  // Compiled and interpreted functions (rather than p.d.f.s) can be made with the lower case 
  // 'expr' and 'cexpr' types

  // Print workspace contents
  w->Print() ;

  // Make workspace visible on command line
  gDirectory->Add(w) ;
}


