//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 02.01.01.0784
// ----------------------------------------------------------------------------
// Standard INDIClient Process Module Version 01.00.03.0102
// ----------------------------------------------------------------------------
// INDICCDFrameInterface.h - Released 2016/03/18 13:15:37 UTC
// ----------------------------------------------------------------------------
// This file is part of the standard INDIClient PixInsight module.
//
// Copyright (c) 2014-2016 Klaus Kretzschmar
//
// Redistribution and use in both source and binary forms, with or without
// modification, is permitted provided that the following conditions are met:
//
// 1. All redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. All redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. Neither the names "PixInsight" and "Pleiades Astrophoto", nor the names
//    of their contributors, may be used to endorse or promote products derived
//    from this software without specific prior written permission. For written
//    permission, please contact info@pixinsight.com.
//
// 4. All products derived from this software, in any form whatsoever, must
//    reproduce the following acknowledgment in the end-user documentation
//    and/or other materials provided with the product:
//
//    "This product is based on software from the PixInsight project, developed
//    by Pleiades Astrophoto and its contributors (http://pixinsight.com/)."
//
//    Alternatively, if that is where third-party acknowledgments normally
//    appear, this acknowledgment must be reproduced in the product itself.
//
// THIS SOFTWARE IS PROVIDED BY PLEIADES ASTROPHOTO AND ITS CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PLEIADES ASTROPHOTO OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, BUSINESS
// INTERRUPTION; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; AND LOSS OF USE,
// DATA OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------

#ifndef __INDICCDFrameInterface_h
#define __INDICCDFrameInterface_h

#include <pcl/ComboBox.h>
#include <pcl/Label.h>
#include <pcl/NumericControl.h>
#include <pcl/ProcessInterface.h>
#include <pcl/PushButton.h>
#include <pcl/SectionBar.h>
#include <pcl/Sizer.h>
#include <pcl/SpinBox.h>
#include <pcl/Timer.h>

#include "INDIClient.h"

namespace pcl
{

// ----------------------------------------------------------------------------

class INDICCDFrameInterface : public ProcessInterface
{
public:

   INDICCDFrameInterface();
   virtual ~INDICCDFrameInterface();

   virtual IsoString Id() const;
   virtual MetaProcess* Process() const;
   virtual const char** IconImageXPM() const;
   virtual InterfaceFeatures Features() const;
   virtual void ResetInstance();
   virtual bool Launch( const MetaProcess&, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/ );
   virtual ProcessImplementation* NewProcess() const;
   virtual bool ValidateProcess( const ProcessImplementation&, String& whyNot ) const;
   virtual bool RequiresInstanceValidation() const;
   virtual bool ImportProcess( const ProcessImplementation& );

private:

   String m_device;

   struct GUIData
   {
      GUIData( INDICCDFrameInterface& );

      Timer UpdateDeviceList_Timer;
      Timer UpdateDeviceProperties_Timer;

      VerticalSizer     Global_Sizer;
         SectionBar        CCDParam_SectionBar;
         Control           CCDParam_Control;
         VerticalSizer     CCDParam_Sizer;
            HorizontalSizer   CCDDevice_Sizer;
               Label             CCDDevice_Label;
               ComboBox          CCDDevice_Combo;
            Control           CCDProperties_Control;
            VerticalSizer     CCDProperties_Sizer;
               HorizontalSizer   CCDTemp_HSizer;
                  NumericEdit       CCDTemp_NumericEdit;
                  NumericControl    CCDTargetTemp_NumericEdit;
                  PushButton        CCDTargetTemp_PushButton;
               HorizontalSizer   CCDBinX_HSizer;
                  Label             CCDBinX_Label;
                  ComboBox          CCDBinX_Combo;
               HorizontalSizer   CCDBinY_HSizer;
                  Label             CCDBinY_Label;
                  ComboBox          CCDBinY_Combo;
               HorizontalSizer   CCDFrameType_HSizer;
                  Label             CCDFrameType_Label;
                  ComboBox          CCDFrameType_Combo;
               HorizontalSizer   UploadMode_HSizer;
                  Label               UploadMode_Label;
                  ComboBox            UploadMode_Combo;
               HorizontalSizer   UploadDir_HSizer;
                  Label               UploadDir_Label;
                  Edit                UploadDir_Edit;
                  PushButton          UploadDir_PushButton;
               HorizontalSizer   ServerFileNameTemplate_HSizer;
                  Label               ServerFileNameTemplate_Label;
                  Edit                ServerFileNameTemplate_Edit;
                  PushButton          ServerFileNameTemplate_PushButton;
         SectionBar        FrameAcquisition_SectionBar;
         Control           FrameAcquisition_Control;
         VerticalSizer     FrameAcquisition_Sizer;
            NumericEdit       ExposureTime_NumericEdit;
            NumericEdit       ExposureDelay_NumericEdit;
            HorizontalSizer   ExposureCount_Sizer;
               Label             ExposureCount_Label;
               SpinBox           ExposureCount_SpinBox;
   };

   GUIData* GUI;

   void UpdateControls();

   void e_Show( Control& );
   void e_Hide( Control& );
   void e_Timer( Timer& sender );
   void e_Click( Button& sender, bool checked );
   void e_ItemSelected( ComboBox& sender, int itemIndex );
};

// ----------------------------------------------------------------------------

PCL_BEGIN_LOCAL
extern INDICCDFrameInterface* TheINDICCDFrameInterface;
PCL_END_LOCAL

// ----------------------------------------------------------------------------

} // pcl

#endif   // __INDICCDFrameInterface_h

// ----------------------------------------------------------------------------
// EOF INDICCDFrameInterface.h - Released 2016/03/18 13:15:37 UTC
