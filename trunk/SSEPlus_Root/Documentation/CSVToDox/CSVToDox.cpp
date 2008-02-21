//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef std::vector< std::string  > StringList;

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
        list.push_back( Trim(tmp) );            
    }        
    return list;
}

size_t GetWidth( const char * filename )
{
    size_t width = 0;
    char buffer[5000];

    std::ifstream file( filename );
    if( !file )
    {
        std::cout << "File: " << filename << " not found"<< std::endl;
        return 0;
    }

    while( !file.eof() )
    {
        file.getline( buffer, sizeof(buffer) );  
        StringList list = ParseList( buffer );

        if( list.size() > width )
        {
            width = list.size();
        } 
    }
    return width;
}

void Convert( const char * filename )
{
    size_t width = GetWidth( filename );
    std::ifstream file( filename );    

    std::cout << "/**" << std::endl;
    std::cout << "\\page fnTable Function Table" << std::endl;
    std::cout << "<table>" << std::endl;
    char buffer[5000];

    file.getline( buffer, sizeof(buffer) );  
    StringList header = ParseList( buffer );

    if( width != header.size() )
    {
        std::cout << "ERROR: Inconsistent header file size." <<std::endl;
        return;
    }

    std::cout << "<tr>" << std::endl;
    for( size_t i=0; i<header.size(); ++i )
    {
        std::cout << "  <th>" << header[i] << "</th>" << std::endl;
    }

    std::cout << "</tr>" << std::endl;

    while( !file.eof() )
    {
        file.getline( buffer, sizeof(buffer) );  
        StringList list = ParseList( buffer );

        if( 0 == list.size() )
            break;

        if( 0 == list[0].size() )
            continue;

        std::string name;
        if( 0 == list[0].find("_mm_") )         // find _mm_
        {
            name = list[0].substr(3);
            std::cout<< "<tr><td>\\MSDN{"<< list[0]<< "}</td><td>" << list[1] <<"</td>";
        }
        else if( 0 == list[0].find("_m_") )     // find _m_
        {
            name = list[0].substr(2);
            std::cout<< "<tr><td>"<< list[0]<< "</td><td>" << list[1] <<"</td>";
        }
        else if( 0 == list[0].find("ssp_") )         // find ssp_
        {
            name = list[0].substr(3);
            std::cout<< "<tr><td>"<< list[0]<< "</td><td>" << list[1] <<"</td>";
        }
        else
        {           
            std::cout << "ERROR: Could not parse function name: " << list[0] << std::endl;
            break;
        }   
        

        for( size_t i=2; i<width; ++i )
        {       
            if( i<list.size() && list[i].size() )   // Data present
            {
                std::cout<< "  <td>\\link ssp" << name << "_" << header[i] << "() " << header[i] << "\\endlink</td>" << std::endl;
            }      
            else 
            {
                std::cout<< "  <td>&nbsp;</td>" << std::endl;
            }
        }
        std::cout << "</tr>" << std::endl;          
    }
    std::cout << "</table>" << std::endl;  
    std::cout << "*/";
}

int main( int argc, char ** argv )
{
    switch( argc )
    {
    case 2:
        Convert( argv[1] );
        break;

    default:
        std::cout << "Usage CSVToDox input.csv" << std::endl;
    }
    return 0;
}