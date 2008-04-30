//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __CSVTABLE_H__
#define __CSVTABLE_H__

#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

typedef std::vector< std::string              > StringList;
typedef std::map   < std::string, std::string > StringMap;

struct CSVLine
{
    std::string source;
    double SSE2, SSE3, SSSE3, SSE4a, SSE4_1, SSE4_2, SSE5;
    bool used;

    CSVLine():SSE2(0),SSE3(0),SSSE3(0),SSE4a(0),SSE4_1(0),SSE4_2(0),SSE5(0){}

    CSVLine( StringMap & line )
    {
        source = line[ "Source" ];
        SSE2   = atof( line[ "SSE2" ].c_str() );
        SSE3   = atof( line[ "SSE3" ].c_str() );
        SSSE3  = atof( line[ "SSSE3"].c_str() );
        SSE4a  = atof( line[ "SSE4A"].c_str() );
        SSE4_1 = atof( line[ "SSE41"].c_str() );
        SSE4_2 = atof( line[ "SSE42"].c_str() );
        SSE5   = atof( line[ "SSE5" ].c_str() );
        used   = false;
    }

    std::string ToString() const
    {
        std::ostringstream oss;
        oss << "[" << source << "]," << SSE2 << "," << SSE3 << "," << SSSE3 << "," << SSE4a << "," << SSE4_1 << "," << SSE4_2 << "," << SSE5;
        return oss.str();
    }
};

class CSVTable
{
    typedef std::map< std::string, CSVLine > LineMap;
    LineMap map;

    std::string Trim( std::string s)
    {
        std::string r=s.erase(   s.find_last_not_of (" ")+1 );
        return        r.erase( 0,r.find_first_not_of(" ")   );
    }

    StringList ParseList( const std::string & buffer )
    {
        StringList list;             
        for( size_t i=0,pos=0,end=0; end<std::string::npos; pos=end+1,++i )
        {
            std::string tmp;
            end = buffer.find  ( ",", pos     );
            tmp = buffer.substr( pos, end-pos );          
            list.push_back( Trim( tmp ) );            
        }        
        return list;
    }

    StringMap Combine( const StringList header, const StringList row )
    {
        StringMap map;
        for( size_t i=0; i<header.size() && i<row.size(); ++i )
        {
            map[ header[i] ] = row[i];  
        }
        return map;
    }

public:
    CSVTable( const char * filename )
    {
        char buffer[1024];
        std::ifstream f( filename );

        if( !f )
        {
            std::cout << "ERROR: Could not open file: " << filename << std::endl;
            return;
        }

        if( !f.eof() )
        {
            f.getline( buffer, sizeof(buffer) );  
            StringList header = ParseList( buffer );         // Read the header      

            while( !f.eof() )
            {
                f.getline( buffer, sizeof(buffer) );  

                std::string tmp = Trim( std::string( buffer) );

                if( tmp.size() )
                {
                    StringList row = ParseList( tmp );        // Read a row
                    
                    StringMap record = Combine( header, row );  
                    map[ record["Name"] ] = CSVLine(record); 
                }
            }
        }        
    }

    const CSVLine & operator[]( const std::string & name )
    {   
        CSVLine & tmp = map[ name ];
        tmp.used = true;
        return tmp;
    }

    std::string UnusedEntriesString()
    {
        std::ostringstream oss;

        for( LineMap::const_iterator it=map.begin(); it!=map.end(); ++it )
        {
            if( !it->second.used )
            {
                oss << std::left << std::setw(30) << it->first << "," << it->second.ToString() << std::endl;
            }
        }       

        return oss.str();
    }    
};

/* USAGE

    CSVTable csv( "test.csv" );

    std::cout << csv[ "A" ].ToString() << std::endl;
    std::cout << csv[ "B" ].SSE3       << std::endl;

*/

#endif // __CSVTABLE_H__
