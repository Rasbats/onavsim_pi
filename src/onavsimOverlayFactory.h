/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  onavsim Plugin Freinds
 * Author:   David Register
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#include <map>
#include <wx/string.h>
#include "bbox.h"

#ifdef ocpnUSE_GL
#ifdef __WXMSW__
#include <GL/glu.h>
#include "GL/gl.h"  // local copy for Windows
#else

#ifndef __OCPN__ANDROID__
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include "GL/gl_private.h"
#include "qopengl.h"  // this gives us the qt runtime gles2.h
#endif

#endif
#endif

using namespace std;



//----------------------------------------------------------------------------------------------------------
//    onavsim Overlay Specification
//----------------------------------------------------------------------------------------------------------

class onavsimOverlay {
public:
    onavsimOverlay( void )
    {
        m_iTexture = 0;
        m_pDCBitmap = NULL, m_pRGBA = NULL;
    }

    ~onavsimOverlay( void )
    {
        if(m_iTexture)
          glDeleteTextures( 1, &m_iTexture );
        delete m_pDCBitmap, delete[] m_pRGBA;
    }

    unsigned int m_iTexture; /* opengl mode */

    wxBitmap *m_pDCBitmap; /* dc mode */
    unsigned char *m_pRGBA;

    int m_width;
    int m_height;
};

//----------------------------------------------------------------------------------------------------------
//    onavsim Overlay Factory Specification
//----------------------------------------------------------------------------------------------------------

class onavsimUIDialog;

class onavsimOverlayFactory {
public:
    onavsimOverlayFactory( onavsimUIDialog &dlg );
    ~onavsimOverlayFactory();

    void SetSettings( bool hiDefGraphics, bool GradualColors )
    {
      m_hiDefGraphics = hiDefGraphics;
      m_bGradualColors = GradualColors;
    }

    void SetMessage( wxString message ) { m_Message = message; }
    void SetParentSize( int w, int h ) { m_ParentSize.SetWidth(w) ; m_ParentSize.SetHeight(h) ;}
	bool RenderGLonavsimOverlay( wxGLContext *pcontext, PlugIn_ViewPort *vp );
    bool RenderonavsimOverlay( wxDC &dc, PlugIn_ViewPort *vp );

	void DrawAllCurrentsInViewPort(PlugIn_ViewPort *BBox, bool bRebuildSelList,
        bool bforce_redraw_currents, bool bdraw_mono_for_mask, wxDateTime myTime);

	void DrawNavUnitInViewPort(wxString navName, wxString navType, double rot, int x, int y);

	wxPoint ScaleCurrentArrow(int index, wxPoint myPoint, int scale);

    void Reset();
	wxImage &DrawGLText( double value, int precision);
	wxImage &DrawGLTextDir( double value, int precision);
	wxImage &DrawGLTextString( wxString myText);
	wxImage &DrawGLPolygon();

	void DrawGLLabels(onavsimOverlayFactory *pof, wxDC *dc,
                               PlugIn_ViewPort *vp,
                               wxImage &imageLabel, double myLat, double myLon, int offset);

	void drawGLPolygons(onavsimOverlayFactory *pof, wxDC *dc,
                                PlugIn_ViewPort *vp, 
                                wxImage &imageLabel, double myLat, double myLon, int offset );

	void DrawGLLine( double x1, double y1, double x2, double y2, double width, wxColour myColour );
    void DrawOLBitmap( const wxBitmap &bitmap, wxCoord x, wxCoord y, bool usemask );
	bool              m_bShowRate;
    bool              m_bShowDirection;
	bool			  m_bHighResolution;
	bool              m_bShowFillColour;
	wxString		  m_sShowScale;
	wxDateTime        m_dtUseNew;
	bool outsideChartScale;

private:

	bool inGL;
	
    bool DoRenderonavsimOverlay( PlugIn_ViewPort *vp );	
    void DrawMessageWindow( wxString msg, int x, int y , wxFont *mfont);

    wxColour GetSpeedColour(double my_speed);

    bool drawCurrentArrow(int x, int y, double rot_angle, double scale, double rate );


    double m_last_vp_scale;

	//  for GL
	wxColour c_GLcolour;
	wxPoint p_basic[9];
	//
    wxString m_Message;
    wxString m_Message_Hiden;
    wxSize  m_ParentSize;

    wxDC *m_pdc;
    wxGraphicsContext *m_gdc;

    wxFont *m_dFont_map;
    wxFont *m_dFont_war;

    wxFont *pTCFont;

    bool m_hiDefGraphics;
    bool m_bGradualColors;

    wxColour m_text_color;
    std::map < double , wxImage > m_labelCache;
	std::map < wxString , wxImage > m_labelCacheText;

	wxImage m_fillImg;
    onavsimUIDialog &m_dlg;

};
