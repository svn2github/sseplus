//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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

std::string TH( const std::string & str ){ return "\n  <th>" + str + "</th>";  }
std::string TD( const std::string & str ){ return "\n  <td>" + str + "</td>";  }
std::string TDa( const std::string & str ){ return "\n  <td class=\"a\">" + str + "</td>";  }


void Convert( const char * filename )
{
    size_t width = GetWidth( filename );
    std::ifstream file( filename );    

    std::cout << "/**" << std::endl;
    std::cout << "\\page fnTable Function Table" << std::endl;
    std::cout << "<table border=\"0\" cellspacing=\"1\" cellpadding=\"1\">";
    char buffer[5000];

    file.getline( buffer, sizeof(buffer) );  
    StringList header = ParseList( buffer );

    if( width != header.size() )
    {
        std::cout << "ERROR: Inconsistent header file size." <<std::endl;
        return;
    }

   

    for( unsigned int count=0; !file.eof(); ++count )
    {
        // Header
       if( 0 == count%20 )
       {
          std::cout << "\n<tr>";
          for( size_t i=0; i<header.size(); ++i )
          {
              std::cout << TH( header[i] );
          }
          std::cout << "\n</tr>";
       }


        file.getline( buffer, sizeof(buffer) );  
        StringList list = ParseList( buffer );

        if( 0 == list.size() )
            break;

        if( 0 == list[0].size() )
            continue;       
       
        if( 0 != list[0].find("ssp_") )   
        {           
            std::cout << "ERROR: Could not parse function name: " << list[0] << std::endl;
            break;
        }   
        else
        {  
            std::string tmp = list[0];

            if( "SSP" != list[2] ) // Native instruction
            {
               tmp = "\\MSDN{_mm" + list[0].substr(3) + "}";
            }

            std::cout<< "<tr>" << TDa(tmp) << TD( list[1]) << TD( list[2] );
        }            
        

        for( size_t i=3; i<width; ++i )
        {       
            if( i<list.size() && list[i].size() )   // Data present
            {
               std::ostringstream oss;

               oss << "\\link " << list[0] << "_" << header[i] << "() ";// << header[i];
                
                if( "-1" == list[i] )  oss << "X";
                else                   oss << list[i];

                oss << "\\endlink";

                std::cout << TD( oss.str() );
            }      
            else 
            {
                std::cout<< TD( "&nbsp;");
            }
        }
        std::cout << "\n</tr>";         
    }
    std::cout << "\n</table>";  
    std::cout << "\n*/";
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