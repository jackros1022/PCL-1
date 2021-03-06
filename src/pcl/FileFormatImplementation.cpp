//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 02.01.01.0784
// ----------------------------------------------------------------------------
// pcl/FileFormatImplementation.cpp - Released 2016/02/21 20:22:19 UTC
// ----------------------------------------------------------------------------
// This file is part of the PixInsight Class Library (PCL).
// PCL is a multiplatform C++ framework for development of PixInsight modules.
//
// Copyright (c) 2003-2016 Pleiades Astrophoto S.L. All Rights Reserved.
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

#include <pcl/Exception.h>
#include <pcl/FileFormatImplementation.h>

namespace pcl
{

// ----------------------------------------------------------------------------

struct FileFormatProperty
{
   IsoString id;
   Variant   value;

   FileFormatProperty( const IsoString& i, const Variant& v = Variant() ) :
      id( i ),
      value( v )
   {
   }

   FileFormatProperty() = default;

   FileFormatProperty( const FileFormatProperty& ) = default;

   FileFormatProperty& operator =( const FileFormatProperty& ) = default;

   bool operator ==( const FileFormatProperty& x ) const
   {
      return id == x.id;
   }

   bool operator <( const FileFormatProperty& x ) const
   {
      return id < x.id;
   }
};

typedef Array<FileFormatProperty> FileFormatPropertyArray;

// ----------------------------------------------------------------------------

struct FileFormatImplementationPrivate
{
           FITSKeywordArray                keywords;
   mutable FITSKeywordArray::iterator      keywordIterator = nullptr;
           ICCProfile                      iccProfile;
           UInt8Image                      thumbnail;
           FileFormatPropertyArray         properties;
           RGBColorSystem                  rgbws;
           DisplayFunction                 displayFunction;
           ColorFilterArray                colorFilterArray;

   FileFormatImplementationPrivate() = default;
};

// ----------------------------------------------------------------------------

FileFormatImplementation::FileFormatImplementation( const MetaFileFormat* m ) :
   meta( m )
{
}

FileFormatImplementation::~FileFormatImplementation()
{
   /*
    * The following would only happen upon a catastrophic situation. Under
    * normal operation, the PI core application will always close files prior
    * to instance destruction.
    *
    * if ( IsOpen() )
    *   Close();
    *
    * Since MSVC seems to have problems with virtual functions called from
    * destructors (even virtual destructors), I decided to comment out the two
    * lines above.
    */
}

// ----------------------------------------------------------------------------

#define MANDATORY( funcName )             \
   __Mandatory( meta->Name(), funcName )

static void __Mandatory( const IsoString& formatName, const char* funcName )
{
   throw Error( String( formatName ) + "FileFormatImplementation: " +
                funcName + "() must be reimplemented in descendant class" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Close()
{
   MANDATORY( "Close" );
}

// ----------------------------------------------------------------------------

bool FileFormatImplementation::IsOpen() const
{
   MANDATORY( "IsOpen" );
   return false;
}

// ----------------------------------------------------------------------------

String FileFormatImplementation::FilePath() const
{
   MANDATORY( "FilePath" );
   return String();
}

// ----------------------------------------------------------------------------

ImageDescriptionArray FileFormatImplementation::Open( const String&, const IsoString& )
{
   MANDATORY( "Open" );
   return ImageDescriptionArray();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::SelectImage( int )
{
   MANDATORY( "SelectImage" );
}

// ----------------------------------------------------------------------------

int FileFormatImplementation::SelectedImageIndex() const
{
   MANDATORY( "SelectedImageIndex" );
   return -1;
}

// ----------------------------------------------------------------------------

void* FileFormatImplementation::FormatSpecificData() const
{
   MANDATORY( "FormatSpecificData" );
   return 0;
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Extract( FITSKeywordArray& )
{
   MANDATORY( "ExtractKeywords" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Extract( ICCProfile& )
{
   MANDATORY( "ExtractICCProfile" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Extract( pcl::UInt8Image& )
{
   MANDATORY( "ExtractThumbnail" );
}

// ----------------------------------------------------------------------------

ImagePropertyDescriptionArray FileFormatImplementation::Properties()
{
   MANDATORY( "Properties" );
   return ImagePropertyDescriptionArray();
}

// ----------------------------------------------------------------------------

Variant FileFormatImplementation::ReadProperty( const IsoString& property )
{
   MANDATORY( "ReadProperty" );
   return Variant();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::WriteProperty( const IsoString& property, const Variant& value )
{
   MANDATORY( "WriteProperty" );
}

// ----------------------------------------------------------------------------

RGBColorSystem FileFormatImplementation::ReadRGBWS()
{
   MANDATORY( "ReadRGBWS" );
   return RGBColorSystem();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::WriteRGBWS( const RGBColorSystem& rgbws )
{
   MANDATORY( "WriteRGBWS" );
}

// ----------------------------------------------------------------------------

DisplayFunction FileFormatImplementation::ReadDisplayFunction()
{
   MANDATORY( "ReadDisplayFunction" );
   return DisplayFunction();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::WriteDisplayFunction( const DisplayFunction& df )
{
   MANDATORY( "WriteDisplayFunction" );
}

// ----------------------------------------------------------------------------

ColorFilterArray FileFormatImplementation::ReadColorFilterArray()
{
   MANDATORY( "ReadColorFilterArray" );
   return ColorFilterArray();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::WriteColorFilterArray( const ColorFilterArray& cfa )
{
   MANDATORY( "WriteColorFilterArray" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::ReadImage( pcl::Image& )
{
   MANDATORY( "ReadImage" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::ReadImage( pcl::DImage& )
{
   MANDATORY( "ReadDImage" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::ReadImage( UInt8Image& )
{
   MANDATORY( "ReadUInt8Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::ReadImage( UInt16Image& )
{
   MANDATORY( "ReadUInt16Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::ReadImage( UInt32Image& )
{
   MANDATORY( "ReadUInt32Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Read( pcl::Image::sample*, int, int, int )
{
   MANDATORY( "ReadIncrementalImage" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Read( pcl::DImage::sample*, int, int, int )
{
   MANDATORY( "ReadIncrementalDImage" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Read( UInt8Image::sample*, int, int, int )
{
   MANDATORY( "ReadIncrementalUInt8Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Read( UInt16Image::sample*, int, int, int )
{
   MANDATORY( "ReadIncrementalUInt16Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Read( UInt32Image::sample*, int, int, int )
{
   MANDATORY( "ReadIncrementalUInt32Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Create( const String&, int, const IsoString& )
{
   MANDATORY( "Create" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::SetFormatSpecificData( const void* )
{
   MANDATORY( "SetFormatSpecificData" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Embed( const FITSKeywordArray& )
{
   MANDATORY( "EmbedKeywords" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Embed( const ICCProfile& )
{
   MANDATORY( "EmbedICCProfile" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Embed( const pcl::UInt8Image& )
{
   MANDATORY( "EmbedThumbnail" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::WriteImage( const pcl::Image& )
{
   MANDATORY( "WriteImage" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::WriteImage( const pcl::DImage& )
{
   MANDATORY( "WriteDImage" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::WriteImage( const UInt8Image& )
{
   MANDATORY( "WriteUInt8Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::WriteImage( const UInt16Image& )
{
   MANDATORY( "WriteUInt16Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::WriteImage( const UInt32Image& )
{
   MANDATORY( "WriteUInt32Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::CreateImage( const ImageInfo& )
{
   MANDATORY( "CreateImage" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Write( const pcl::Image::sample*, int, int, int )
{
   MANDATORY( "WriteIncrementalImage" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Write( const pcl::DImage::sample*, int, int, int )
{
   MANDATORY( "WriteIncrementalDImage" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Write( const UInt8Image::sample*, int, int, int )
{
   MANDATORY( "WriteIncrementalUInt8Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Write( const UInt16Image::sample*, int, int, int )
{
   MANDATORY( "WriteIncrementalUInt16Image" );
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::Write( const UInt32Image::sample*, int, int, int )
{
   MANDATORY( "WriteIncrementalUInt32Image" );
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginPrivate()
{
   if ( m_data.IsNull() )
      m_data = new FileFormatImplementationPrivate;
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginKeywordExtraction()
{
   BeginPrivate();
   m_data->keywords.Clear();
   Extract( m_data->keywords );
   m_data->keywordIterator = m_data->keywords.Begin();
}

size_type FileFormatImplementation::NumberOfKeywords() const
{
   return m_data->keywords.Length();
}

bool FileFormatImplementation::GetNextKeyword( FITSHeaderKeyword& k ) const
{
   if ( m_data->keywordIterator == m_data->keywords.End() )
      return false;
   k = *m_data->keywordIterator++; // N.B.: mutable keywordIterator
   return true;
}

void FileFormatImplementation::EndKeywordExtraction()
{
   m_data->keywords.Clear();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginICCProfileExtraction()
{
   BeginPrivate();
   m_data->iccProfile.Clear();
   Extract( m_data->iccProfile );
}

const ICCProfile& FileFormatImplementation::GetICCProfile() const
{
   return m_data->iccProfile;
}

void FileFormatImplementation::EndICCProfileExtraction()
{
   m_data->iccProfile.Clear();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginThumbnailExtraction()
{
   BeginPrivate();
   m_data->thumbnail.FreeData();
   Extract( m_data->thumbnail );
}

const UInt8Image& FileFormatImplementation::GetThumbnail() const
{
   return m_data->thumbnail;
}

void FileFormatImplementation::EndThumbnailExtraction()
{
   m_data->thumbnail.FreeData();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginPropertyExtraction()
{
   BeginPrivate();
   m_data->properties.Clear();
}

const Variant& FileFormatImplementation::GetImageProperty( const IsoString& id )
{
   IsoString tid = id.Trimmed();
   FileFormatPropertyArray::const_iterator i = m_data->properties.Search( tid );
   if ( i != m_data->properties.End() )
      return i->value;
   m_data->properties.Append( FileFormatProperty( tid, ReadProperty( tid ) ) );
   return m_data->properties.Search( tid )->value;
}

void FileFormatImplementation::EndPropertyExtraction()
{
   m_data->properties.Clear();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginRGBWSExtraction()
{
   BeginPrivate();
   m_data->rgbws = ReadRGBWS();
}

const RGBColorSystem& FileFormatImplementation::GetRGBWS() const
{
   return m_data->rgbws;
}

void FileFormatImplementation::EndRGBWSExtraction()
{
   m_data->rgbws = RGBColorSystem();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginDisplayFunctionExtraction()
{
   BeginPrivate();
   m_data->displayFunction = ReadDisplayFunction();
}

const DisplayFunction& FileFormatImplementation::GetDisplayFunction() const
{
   return m_data->displayFunction;
}

void FileFormatImplementation::EndDisplayFunctionExtraction()
{
   m_data->displayFunction = DisplayFunction();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginColorFilterArrayExtraction()
{
   BeginPrivate();
   m_data->colorFilterArray = ReadColorFilterArray();
}

const ColorFilterArray& FileFormatImplementation::GetColorFilterArray() const
{
   return m_data->colorFilterArray;
}

void FileFormatImplementation::EndColorFilterArrayExtraction()
{
   m_data->colorFilterArray = ColorFilterArray();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginKeywordEmbedding()
{
   BeginPrivate();
   m_data->keywords.Clear();
}

void FileFormatImplementation::AddKeyword( const FITSHeaderKeyword& k )
{
   m_data->keywords.Add( k );
}

void FileFormatImplementation::EndKeywordEmbedding()
{
   Embed( m_data->keywords );
   m_data->keywords.Clear();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginICCProfileEmbedding()
{
   BeginPrivate();
   m_data->iccProfile.Clear();
}

void FileFormatImplementation::SetICCProfile( const ICCProfile& icc )
{
   if ( icc.IsProfile() )
   {
      m_data->iccProfile = icc;
      m_data->iccProfile.SetEmbeddedFlag();
   }
}

void FileFormatImplementation::EndICCProfileEmbedding()
{
   if ( m_data->iccProfile.IsProfile() ) // ### should allow embedding empty profiles here?
      Embed( m_data->iccProfile );
   m_data->iccProfile.Clear();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginThumbnailEmbedding()
{
   BeginPrivate();
   m_data->thumbnail.FreeData();
}

void FileFormatImplementation::SetThumbnail( const UInt8Image& img )
{
   if ( !img.IsEmpty() )
      m_data->thumbnail.Assign( img );
}

void FileFormatImplementation::EndThumbnailEmbedding()
{
   if ( !m_data->thumbnail.IsEmpty() )
   {
      Embed( m_data->thumbnail );
      m_data->thumbnail.FreeData();
   }
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginPropertyEmbedding()
{
   BeginPrivate();
   m_data->properties.Clear();
}

void FileFormatImplementation::SetImageProperty( const IsoString& id, const Variant& value )
{
   IsoString tid = id.Trimmed();
   if ( !tid.IsEmpty() && value.IsValid() )
   {
      FileFormatPropertyArray::iterator i = m_data->properties.Search( tid );
      if ( i != m_data->properties.End() )
         i->value = value;
      else
         m_data->properties.Append( FileFormatProperty( tid, value ) );
   }
}

void FileFormatImplementation::EndPropertyEmbedding()
{
   for ( FileFormatPropertyArray::const_iterator i = m_data->properties.Begin(); i != m_data->properties.End(); ++i )
      WriteProperty( i->id, i->value );
   m_data->properties.Clear();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginRGBWSEmbedding()
{
   BeginPrivate();
   m_data->rgbws = RGBColorSystem();
}

void FileFormatImplementation::SetRGBWS( const RGBColorSystem& rgbws )
{
   m_data->rgbws = rgbws;
}

void FileFormatImplementation::EndRGBWSEmbedding()
{
   WriteRGBWS( m_data->rgbws );
   m_data->rgbws = RGBColorSystem();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginDisplayFunctionEmbedding()
{
   BeginPrivate();
   m_data->displayFunction = DisplayFunction();
}

void FileFormatImplementation::SetDisplayFunction( const DisplayFunction& df )
{
   m_data->displayFunction = df;
}

void FileFormatImplementation::EndDisplayFunctionEmbedding()
{
   if ( !m_data->displayFunction.IsIdentityTransformation() )
      WriteDisplayFunction( m_data->displayFunction );
   m_data->displayFunction = DisplayFunction();
}

// ----------------------------------------------------------------------------

void FileFormatImplementation::BeginColorFilterArrayEmbedding()
{
   BeginPrivate();
   m_data->colorFilterArray = ColorFilterArray();
}

void FileFormatImplementation::SetColorFilterArray( const ColorFilterArray& df )
{
   m_data->colorFilterArray = df;
}

void FileFormatImplementation::EndColorFilterArrayEmbedding()
{
   if ( !m_data->colorFilterArray.IsEmpty() )
      WriteColorFilterArray( m_data->colorFilterArray );
   m_data->colorFilterArray = ColorFilterArray();
}

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------
// EOF pcl/FileFormatImplementation.cpp - Released 2016/02/21 20:22:19 UTC
