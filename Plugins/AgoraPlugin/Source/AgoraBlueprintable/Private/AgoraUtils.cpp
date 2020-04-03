// Copyright (c) 2019 Agora.io. All rights reserved.

#include "AgoraUtils.h"
#include "AgoraBlueprintable.h"
#include "AgoraEngineEventHandler.h"
#include "UECompatibility.h"

#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFileManager.h"

#include <string>
#include <fstream>
#include <stdlib.h>

namespace little_endian_io
{
template <typename Word>
std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
{
   for( ; size; --size, value >>= 8 )
      outs.put( static_cast < char > ( value & 0xFF ) );
   return outs;
}
}

int64 UAgoraUtils::StringToInt64( const FString& String )
{
   if( String.IsEmpty() )
      return 0;

   std::string str( TCHAR_TO_ANSI( *String ) );
   int64 result = atoll( str.c_str() );

   return result;
}

FString UAgoraUtils::CreateAudioFileForSpeakersTest()
{
   FString AudioContentDir;
#if PLATFORM_WINDOWS
   const FString& RelPath = FPaths::ProjectDir();
   const FString& FullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead( *RelPath );

   IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
   FString ContentDir = FPaths::Combine( *FullPath, TEXT( "Content/" ) );
   if( !PlatformFile.DirectoryExists( *ContentDir ) )
   {
      bool bRes = PlatformFile.CreateDirectory( *ContentDir );
      if( !bRes )
      {
         return "";
      }
   }
   AudioContentDir = FPaths::Combine( *ContentDir, TEXT( "Audio/" ) );
   if( !PlatformFile.DirectoryExists( *AudioContentDir ) )
   {
      bool bRes = PlatformFile.CreateDirectory( *AudioContentDir );
      if( !bRes )
      {
         return "";
      }
   }
#endif

#if PLATFORM_MAC
   AudioContentDir = "/Library/Caches/";
#endif
   FString AudioFile = FPaths::Combine( *AudioContentDir, TEXT( "ID_TEST_AUDIO.wav" ) );
   {
      std::ifstream f( TCHAR_TO_ANSI( *AudioFile ) );
      if( f.good() )
      {
         return AudioFile;
      }
   }

   std::ofstream f( TCHAR_TO_ANSI( *AudioFile ), std::ios::binary );

   using namespace little_endian_io;
   // Write the file headers
   f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
   write_word( f, 16, 4 );  // no extension data
   write_word( f, 1, 2 );  // PCM - integer samples
   write_word( f, 2, 2 );  // two channels (stereo file)
   write_word( f, 44100, 4 );  // samples per second (Hz)
   write_word( f, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
   write_word( f, 4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
   write_word( f, 16, 2 );  // number of bits per sample (use a multiple of 8)

   // Write the data chunk header
   size_t data_chunk_pos = f.tellp();
   f << "data----";  // (chunk size to be filled in later)

   // Write the audio samples
   // (We'll generate a single C4 note with a sine wave, fading from left to right)
   constexpr double two_pi = 6.283185307179586476925286766559;
   constexpr double max_amplitude = 32760;  // "volume"

   double hz = 44100;    // samples per second
   double frequency = 261.626;  // middle C
   double seconds = 2.5;      // time

   int N = hz * seconds;  // total number of samples
   for( int n = 0; n < N; n++ )
   {
      double amplitude = ( double ) n / N * max_amplitude;
      double value = sin( ( two_pi * n * frequency ) / hz );
      write_word( f, ( int ) ( amplitude  * value ), 2 );
      write_word( f, ( int ) ( ( max_amplitude - amplitude ) * value ), 2 );
   }

   // (We'll need the final file size to fix the chunk sizes above)
   size_t file_length = f.tellp();

   // Fix the data chunk header to contain the data size
   f.seekp( data_chunk_pos + 4 );
   write_word( f, file_length - data_chunk_pos + 8 );

   // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
   f.seekp( 0 + 4 );
   write_word( f, file_length - 8, 4 );

   f.close();

   return AudioFile;
}
