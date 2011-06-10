//*****************************************************************************
/*!	\file importexport_prop.cpp
 	\brief Defines the callbacks that define the layout and behavior of the 
 	Import Export Demo property page.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
 
 */
//*****************************************************************************

#include <xsi_application.h>
#include <xsi_model.h>
#include <xsi_factory.h>
#include <xsi_customproperty.h>
#include <xsi_parameter.h>
#include <xsi_string.h>
#include <xsi_griddata.h>
#include <xsi_value.h>
#include <xsi_ppglayout.h>
#include <xsi_ppgeventcontext.h>

#define LABEL_MIN 140
#define LABEL_RATIO 40

//*****************************************************************************
/*!	Helper function for accessing the Import Export Demo custom property.
 */
//*****************************************************************************
XSI::CustomProperty GetWebGLExportProp()
{	
	XSI::Application app;
	XSI::Model root = app.GetActiveSceneRoot();
	XSI::CustomProperty prop = root.GetProperties().GetItem(L"WebGLExportProp");
	if (!prop.IsValid())
	{
		prop = root.AddProperty( L"WebGLExportProp" );
	}
	return prop;
}

//*****************************************************************************
/*!	Helper function for getting a parameter from the custom property.
	\param in_strName Name of the option to get.
 */
//*****************************************************************************
XSI::Parameter GetWebGLExportOption( const XSI::CString& in_strName )
{
	XSI::CustomProperty pset = GetWebGLExportProp();
	if (!pset.IsValid()) return XSI::CRef();
	
	XSI::Parameter param = pset.GetParameters().GetItem(in_strName);
	
	if (!param.IsValid())
	{	
		pset.AddParameter(
			in_strName,
			XSI::CValue::siInt4,
			XSI::siReadOnly,
			L"",
			L"",
			(LONG)0,
			(LONG)0,
			(LONG)100,
			(LONG)0,
			(LONG)100,
			param);	
	}
	return param;
}

//*****************************************************************************
/*!	Callback that defines the parameters (options) of the custom property.
	\param in_ctxt The context that encapsulates the custom property to initialize.
 */
//*****************************************************************************

XSIPLUGINCALLBACK
XSI::CStatus WebGLExportProp_Define( XSI::CRef& in_ctxt )
{
	XSI::Context ctxt( in_ctxt );
	XSI::CustomProperty pset( ctxt.GetSource() );
	
	XSI::Parameter param;
	/*pset.AddParameter(L"ConstMode",XSI::CValue::siInt4,XSI::siPersistable,L"",L"",(LONG)0,(LONG)0,(LONG)4,(LONG)0,(LONG)4,param);
	pset.AddParameter(L"Subd_level",XSI::CValue::siInt4,XSI::siPersistable,L"",L"",(LONG)0,(LONG)0,(LONG)6,(LONG)0,(LONG)6,param);
	pset.AddParameter(L"Subd_type",XSI::CValue::siInt4,XSI::siPersistable,L"",L"",(LONG)0,(LONG)0,(LONG)3,(LONG)0,(LONG)3,param);
	pset.AddParameter(L"DiscAngle",XSI::CValue::siDouble,XSI::siPersistable,L"",L"",(LONG)0,(LONG)0,(LONG)360,(LONG)0,(LONG)360,param);
	pset.AddParameter(L"UseDisc",XSI::CValue::siBool, XSI::siPersistable, L"", L"", false, param );	
	pset.AddParameter(L"MeshChunkSize",XSI::CValue::siInt4,XSI::siPersistable,L"",L"",(LONG)100,param);
	*/
	XSI::Application app;
	
	XSI::CString strDefaultFile( app.GetInstallationPath( XSI::siProjectPath ) );
	strDefaultFile += L"\\webgl_export";
	
	pset.AddParameter(L"ExportDir",XSI::CValue::siString, XSI::siPersistable, L"", L"", strDefaultFile, param );
	pset.AddParameter(L"CanvasWidth",XSI::CValue::siInt4, XSI::siPersistable, L"", L"", (LONG)600,(LONG)0,(LONG)2400,(LONG)0,(LONG)2400,param);
	pset.AddParameter(L"CanvasHeight",XSI::CValue::siInt4, XSI::siPersistable, L"", L"",(LONG)400,(LONG)0,(LONG)2400,(LONG)0,(LONG)2400,param);

	pset.AddParameter(	L"BackgroundColorR",XSI::CValue::siDouble,  XSI::siPersistable, 
						L"BackgroundColor",	// The name of the first parameter appears as the label
						L"",	
						0.0, 0.0, 1.0, 0.0, 1.0, param ) ;	
	pset.AddParameter(	L"BackgroundColorG",XSI::CValue::siDouble,  XSI::siPersistable, 
						L"", L"",	
						0.0, 0.0, 1.0, 0.0, 1.0, param ) ;	
	pset.AddParameter(	L"BackgroundColorB",XSI::CValue::siDouble,  XSI::siPersistable, 
						L"", L"",	
						0.0, 0.0, 1.0, 0.0, 1.0, param ) ;

	
	
	return XSI::CStatus::OK;
}

//*****************************************************************************
/*!	Callback that defines the layout of controls on the property page.
	\param in_ctxt The context that encapsulates the custom property layout to 
	initialize.
 */
//*****************************************************************************
XSIPLUGINCALLBACK
XSI::CStatus WebGLExportProp_DefineLayout( XSI::CRef& in_ctxt )
{	
	XSI::Context ctxt(in_ctxt);
	XSI::PPGLayout ppg = ctxt.GetSource() ;

	ppg.Clear();
	/*
	// define the geometry section
	ppg.AddGroup(L"Geometry");
	
	LONG labelMinPixels = LABEL_MIN;
	LONG labelPercentage = LABEL_RATIO;

	XSI::CValueArray uiModeItems(10) ;
	uiModeItems[0] = L"Modeling" ; 
	uiModeItems[1] = (LONG)XSI::siConstructionModeModeling;
	uiModeItems[2] = L"Primary Shape" ; 
	uiModeItems[3] = (LONG)XSI::siConstructionModePrimaryShape;
	uiModeItems[4] = L"Animation" ; 
	uiModeItems[5] = (LONG)XSI::siConstructionModeAnimation;
	uiModeItems[6] = L"Secondary Shape" ; 
	uiModeItems[7] = (LONG)XSI::siConstructionModeSecondaryShape;
	uiModeItems[8] = L"Default" ; 
	uiModeItems[9] = (LONG)XSI::siConstructionModeDefault;

	XSI::PPGItem item = ppg.AddEnumControl(
		L"ConstMode",
		uiModeItems,
		L"Choice",
		XSI::siControlCombo ) ;
	item.PutLabel(L"Construction Mode");

	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );
	
	item = ppg.AddItem( L"Subd_level" ) ;
	item.PutLabel(L"Subdivision level");
	
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );

	XSI::CValueArray uiSubdTypeItems(6) ;
	uiSubdTypeItems[0] = L"Catmull-Clark" ; 
	uiSubdTypeItems[1] = (LONG)XSI::siCatmullClark;
	uiSubdTypeItems[2] = L"XSI-Doo-Sabin" ; 
	uiSubdTypeItems[3] = (LONG)XSI::siXSIDooSabin;
	uiSubdTypeItems[4] = L"Linear" ; 
	uiSubdTypeItems[5] = (LONG)XSI::siLinearSubdivision;

	item = ppg.AddEnumControl(
		L"Subd_type",
		uiSubdTypeItems,
		L"Choice",
		XSI::siControlCombo ) ;
	item.PutLabel(L"Subdivision Rule Type");
		
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );

	item = ppg.AddItem( L"DiscAngle" ) ;
	item.PutLabel(L"Discontinuity Angle");
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );

	item = ppg.AddItem( L"UseDisc" ) ;
	item.PutLabel(L"Use Discontinuity");
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );

	ppg.EndGroup();
	*/
	// define the webgl section
	LONG labelMinPixels = LABEL_MIN;
	LONG labelPercentage = LABEL_RATIO;

	ppg.AddGroup(L"WebGL");

	XSI::PPGItem item = ppg.AddItem( L"ExportDir" ) ;
	item.PutLabel(L"Export directory");	
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );
	
	item = ppg.AddItem( L"CanvasWidth" ) ;
	item.PutLabel(L"Canvas width");
	
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );
	
	item = ppg.AddItem( L"CanvasHeight" ) ;
	item.PutLabel(L"Canvas height");
	
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );

	item = ppg.AddColor( L"BackgroundColorR", L"BackgroundColor", false ) ;
	item.PutLabel(L"Background color");	
	item.PutLabelMinPixels( labelMinPixels );
 	item.PutLabelPercentage( labelPercentage );
	
	ppg.AddSpacer(10, 20 );

	ppg.AddRow();
	ppg.AddSpacer(75, 1 );
	item = ppg.AddButton( L"ExportMeshButton", L"Export" );

	item.PutAttribute( XSI::siUICX, (LONG)200 );
	ppg.EndRow();
	ppg.AddSpacer(10, 20 );
	ppg.EndGroup();
	
	return XSI::CStatus::OK;
}

//*****************************************************************************
/*!	Callback that handles UI events (such as button clicks) on property page.
	page.
	\param in_ctxt The context that encapsulates the custom property property
	page event.
 */
//*****************************************************************************

XSIPLUGINCALLBACK
XSI::CStatus WebGLExportProp_PPGEvent( const XSI::CRef& in_ctxt )
{	
	XSI::Application app ;

	XSI::PPGEventContext ctxt( in_ctxt ) ;

	XSI::PPGEventContext::PPGEvent eventID = ctxt.GetEventID() ;
	if ( eventID == XSI::PPGEventContext::siButtonClicked )
	{
		XSI::CValue buttonPressed = ctxt.GetAttribute( L"Button" ) ;	
		
		if ( buttonPressed.GetAsText() == L"ExportMeshButton" )
		{
			XSI::CustomProperty in_pset = ctxt.GetSource();
			
			XSI::CValueArray args(5);
			/*args[0] = in_pset.GetParameterValue( L"ConstMode" );
			args[1] = in_pset.GetParameterValue( L"Subd_type" );
			args[2] = in_pset.GetParameterValue( L"Subd_level" );*/
			args[0] = in_pset.GetParameterValue( L"CanvasWidth" );
			args[1] = in_pset.GetParameterValue( L"CanvasHeight" );
			args[2] = in_pset.GetParameterValue( L"BackgroundColorR" );
			args[3] = in_pset.GetParameterValue( L"BackgroundColorG" );
			args[4] = in_pset.GetParameterValue( L"BackgroundColorB" );
			
			XSI::CValue retVal;
			XSI::Application app;
			app.ExecuteCommand( L"WebGLExportScene", args, retVal ) ;	
		}				
	}
	
	return XSI::CStatus::OK ;
}
