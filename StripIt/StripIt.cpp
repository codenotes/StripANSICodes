// StripIt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" //precompiled header on windows

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <boost/fusion/adapted.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/any.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/home/x3/binary.hpp> 
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include<boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/include/vector_fwd.hpp>
#include <boost/algorithm/string.hpp>
#include "boost/range/irange.hpp"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

#include <map>
#include <iostream>




#include "C:\Dropbox\usr\include\x3\helpfull_defines.h"

using namespace boost::multi_index;

#pragma region defines

#define ESC							"\033"
#define RESET_DEF					"\033[0m"
#define BLACK_DEF					"\033[30m"    
#define GREEN_DEF					"\033[32m"    
#define YELLOW_DEF					"\033[33m"    
#define BLUE_DEF					"\033[34m"    
#define MAGENTA_DEF					"\033[35m"    
#define CYAN_DEF					"\033[36m"    
#define WHITE_DEF					"\033[37m"    
#define RED_DEF						"\033[31m"    

#define BOLDBLACK_DEF				"\033[1m\033[30m"		 
#define BOLDRED_DEF					"\033[1m\033[31m"		 
#define BOLDGREEN_DEF				"\033[1m\033[32m"		 
#define BOLDYELLOW_DEF				"\033[1m\033[33m"		 
#define BOLDBLUE_DEF				"\033[1m\033[34m"		 
#define BOLDMAGENTA_DEF				"\033[1m\033[35m"		 
#define BOLDCYAN_DEF				"\033[1m\033[36m"		 
#define BOLDWHITE_DEF				"\033[1m\033[37m"		 

#define REDBAR_BOLDWHITE_DEF		"\033[1m\033[41m"		
#define YELLOWBAR_BOLDWHITE_DEF		"\033[1m\033[43m"		
#define BLUEBAR_BOLDWHITE_DEF		"\033[1m\033[44m"		
#define PURPLEBAR_BOLDWHITE_DEF		"\033[1m\033[45m"	
#define AQUABAR_BOLDWHITE_DEF		"\033[1m\033[46m"	
#define GREYBAR_BOLDWHITE_DEF		"\033[1m\033[47m"	

#define REDBAR_BLACK_DEF			"\033[31;7m"			
#define BLACKBAR_RED_DEF			"\033[31;8m"	
#define GREENBAR_BLACK_DEF			"\033[32;7m"			
#define BLACKBAR_GREEN_DEF			"\033[32;8m"	
#define YELLOWBAR_BLACK_DEF			"\033[33;7m"			
#define BLACKBAR_YELLOW_DEF			"\033[33;8m"	
#define BLUEBAR_BLACK_DEF			"\033[34;7m"			
#define BLACKBAR_BLUE_DEF			"\033[34;8m"	
#define PURPLEBAR_BLACK_DEF			"\033[35;7m"			
#define BLACKBAR_PURPLE_DEF			"\033[35;8m"	
//aqua white
#define AQUABAR_BLACK_DEF			"\033[36;7m"			
#define BLACKBAR_AQUA_DEF			"\033[36;8m"	
#define WHITEBAR_BLACK_DEF			"\033[37;7m"			
#define BLACKBAR_WHITE_DEF			"\033[37;8m"	

#define WHITEBAR_RED_DEF			"\033[41;7m"			
#define REDBAR_WHITE_DEF			"\033[41;8m"	

//green
#define WHITEBAR_GREEN_DEF			"\033[42;7m"			
#define GREENBAR_WHITE_DEF			"\033[42;8m"
//mustard bue purple
#define WHITEBAR_MUSTARD_DEF		"\033[43;7m"			
#define MUSTARDBAR_WHITE_DEF		"\033[43;8m"

#define WHITEBAR_BLUE_DEF			"\033[44;7m"			
#define BLUEBAR_WHITE_DEF			"\033[44;8m"

#define WHITEBAR_PURPLE_DEF			"\033[45;7m"			
#define PURPLEBAR_WHITE_DEF			"\033[45;8m"
#define WHITEBAR_AQUA_DEF			"\033[46;7m"			
#define AQUABAR_WHITE_DEF			"\033[46;8m"


#define INVERSEMAJ_DEF				"\033[45;7m"			
#define INVERSEYELLOW_DEF			"\033[43;7m"		



#define GREENBARWHITE_DEF			"\033[42;8m"		  
#define ESC_DEF						"\x1b"
#define CSI_DEF						"\x1b["
#define CSI_CLEAR_SCREEN			 "\033[2J"

#define SCROLL_DEF					"\033[%d;%dr" /*top,buttom*/

#define REPORTPOS					"\033[6n" //puts location in inputstream
#define CURSOR_SAVE					"\033[s" //these are stored in console memory, we never get these values directly
#define CURSOR_RESTORE				"\033[u"
#define CURSOR_HIDE					ESC"[?25l"
#define CURSOR_SHOW					ESC"[?25h"

#define ICH							ESC"[%d@"/*	ICH	Insert Character	Insert <n> spaces at the current cursor position, shifting all existing text to the right. Text exiting the screen to the right is removed.*/
#define DCH							ESC"[%dP"/*	DCH	Delete Character	Delete <n> characters at the current cursor position, shifting in space characters from the right edge of the screen.*/
#define ECH							ESC"[%dX"/*	ECH	Erase Character	Erase <n> characters from the current cursor position by overwriting them with a space character.*/
#define IL							ESC"[%dL"/*	IL	Insert Line	Inserts <n> lines into the buffer at the cursor position. The line the cursor is on, and lines below it, will be shifted downwards.*/
//#define DL							ESC"[%dM"/*   Delete line */
#define DL							ESC"\x1b[2K"

#define CUU							ESC"A"	/*Cursor Up by 1*/
#define CUD							ESC"B"	/*Cursor Down by 1*/
#define CUF							ESC"C"/*Cursor Forward(Right) by 1*/
#define CUB							ESC"D"/*Cursor Backward(Left) by 1*/



#define NO_WRAP						"\x1b\[7l"
#define ENABLE_WRAP					"\x1b\[7h"

#define ED							ESC"[%dJ"/*  Replace all text in the current viewport/screen specified by <n> with space  */
#define EL							ESC"[%dK"/*  Replace all text on the line with the cursor specified by <n> with space  */

#define SU							ESC"[%dS"	/*SU	Scroll Up	Scroll text up by <n>.Also known as pan down, new lines fill in from the bottom of the screen*/
#define SD							ESC"[%dT"	/*SD	Scroll Down	Scroll down by <n>.Also known as pan up, new lines fill in from the top of the screen*/


#define DEC_LINE_DRAWING_MODE_ON	"\033(0"
#define DEC_LINE_DRAWING_MODE_OFF	"\033(B"


//good to use to go into mode where you don't screw with where you came from
#define USE_ALT_BUFFER				ESC"[?1049h"	/*Use Alternate Screen Buffer	Switches to a new alternate screen buffer.*/
#define USE_MAIN_BUFFER				ESC"[?1049l"	/*Use Alternate Screen Buffer	Switches to the main buffer.*/

#define FORGROUND_DEF 38
#define BACKGROUND_DEF 48
#define FORE_AND_BACKGROUND_CODE	"\033[%d;5;%dm" // 48|38, <color 0-255>
#define CUR_POS						"\033[%d;%dH" //boost::format("\033[%1%;%2%H") % 15 % 1


#pragma endregion defines


struct ANSIColor
{
	int theColorDef;
};

BOOST_FUSION_ADAPT_STRUCT(ANSIColor,
(int, theColorDef)
)


//ANSI escape sequences to change color and highlighting
struct symb_ansi : public boost::spirit::x3::symbols<ANSIColor>
{

	enum colors
	{
		NONE,
		RESET,
		BLACK,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		RED,
		BOLDBLACK,
		BOLDRED,
		BOLDGREEN,
		BOLDYELLOW,
		BOLDBLUE,
		BOLDMAGENTA,
		BOLDCYAN,
		BOLDWHITE,
		INVERSEMAJ,
		INVERSEYELLOW,
		GREENBARWHITE,
		ESC_,
		CSI
	};

	std::map<enum colors, std::string> colorMap =
	{
		{ NONE, RESET_DEF } ,
	{ RESET ,RESET_DEF } ,
	{ BLACK,BLACK_DEF },
	{ GREEN,GREEN_DEF },
	{ YELLOW, YELLOW_DEF },
	{ BLUE,BLUE_DEF },
	{ MAGENTA,MAGENTA_DEF },
	{ CYAN, CYAN_DEF },
	{ WHITE,WHITE_DEF },
	{ RED,RED_DEF },
	{ BOLDBLACK,BOLDBLACK_DEF },
	{ BOLDRED,BOLDRED_DEF },
	{ BOLDGREEN,BOLDGREEN_DEF },
	{ BOLDYELLOW,BOLDYELLOW_DEF },
	{ BOLDBLUE,BOLDBLUE_DEF },
	{ BOLDMAGENTA,BOLDMAGENTA_DEF },
	{ BOLDCYAN,BOLDCYAN_DEF },
	{ BOLDWHITE,BOLDWHITE_DEF },
	{ INVERSEMAJ,INVERSEMAJ_DEF },
	{ INVERSEYELLOW,INVERSEYELLOW_DEF },
	{ GREENBARWHITE,GREENBARWHITE_DEF },
	{ ESC_,ESC_DEF },
	{ CSI, CSI_DEF }

	};


	struct ansi_code
	{
		colors colorEnum;
		std::string codeString;
	};

	struct IdxColorEnum {};
	struct IdxCodeString {};

	typedef multi_index_container<
		ansi_code,
		indexed_by<
		hashed_unique<
		tag<IdxCodeString>,
		member<
		ansi_code, std::string, &ansi_code::codeString
		>
		>,
		hashed_unique<
		tag<IdxColorEnum>,
		member<
		ansi_code, colors, &ansi_code::colorEnum
		>
		>
		>
	> ansi_code_multi;

	ansi_code_multi acm = {
		{ NONE, RESET_DEF } ,
	{ RESET ,RESET_DEF } ,
	{ BLACK,BLACK_DEF },
	{ GREEN,GREEN_DEF },
	{ YELLOW, YELLOW_DEF },
	{ BLUE,BLUE_DEF },
	{ MAGENTA,MAGENTA_DEF },
	{ CYAN, CYAN_DEF },
	{ WHITE,WHITE_DEF },
	{ RED,RED_DEF },
	{ BOLDBLACK,BOLDBLACK_DEF },
	{ BOLDRED,BOLDRED_DEF },
	{ BOLDGREEN,BOLDGREEN_DEF },
	{ BOLDYELLOW,BOLDYELLOW_DEF },
	{ BOLDBLUE,BOLDBLUE_DEF },
	{ BOLDMAGENTA,BOLDMAGENTA_DEF },
	{ BOLDCYAN,BOLDCYAN_DEF },
	{ BOLDWHITE,BOLDWHITE_DEF },
	{ INVERSEMAJ,INVERSEMAJ_DEF },
	{ INVERSEYELLOW,INVERSEYELLOW_DEF },
	{ GREENBARWHITE,GREENBARWHITE_DEF },
	{ ESC_,ESC_DEF },
	{ CSI, CSI_DEF } };

	symb_ansi()
	{
		codeStringToEnum();
	}

	template<typename Tidx, typename Trecord>
	void IterateOver(
		const Tidx& idx,
		std::function<void(const Trecord& rec)> func
	)
	{
		auto it = idx.begin();
		while (it != idx.end())
		{
			func(*it++);
		}
	}


	void codeStringToEnum()
	{
		auto& idxString = acm.get<IdxCodeString>();
		IterateOver<decltype(idxString), ansi_code>(
			idxString,
			[&](const ansi_code& ac
				)
		{
			//std::cout << ac.codeString << "test" << RESET_DEF << std::endl;

			add(ac.codeString, ANSIColor{ ac.colorEnum });

		});


	}


};


//main parsing code here

namespace x3 = boost::spirit::x3;
using namespace std;
symb_ansi sy;
namespace x3 = boost::spirit::x3;


auto const magic_token = x3::char_('\033');
auto const all_but_magic_token = x3::rule<struct nonsense, std::string>() = *(~magic_token);



//what we want to do is capture where the start and finish of this token is in the parse stream instead of just eat it.
//likely we need a x3:variant ast or I would even be happy with a semantic action that puts these positions in an global vector or map
//I am not not clear how I can obtain these locations.
auto const eat_escape = x3::rule<struct crap>() = sy;




auto green_test = x3::rule<struct asd>() = x3::string(GREEN_DEF);

auto  clean_string = x3::rule<struct nonsense1, vector<std::string>>("clean_string");
auto  clean_string_def = x3::rule<struct nonsense1, vector<std::string>>() =
-all_but_magic_token % eat_escape;

BOOST_SPIRIT_DEFINE(clean_string);


//Bonus ( look at this later, but it is other main question)...
/*

How is it possible to get all my rules in a scope of some kind?  neither BOOST_SPIRIT_DEFINE nor BOOST_SPIRIT_DECLARE seem
to work because of their template intantiations.

*/
#if 0
void rulesInAFunction()
{

	namespace x3 = boost::spirit::x3;
	using namespace std;
	symb_ansi sy;
	namespace x3 = boost::spirit::x3;


	auto const magic_token = x3::char_('\033');
	auto const all_but_magic_token = x3::rule<struct nonsense, std::string>() = *(~magic_token);



	//what we want to do is capture where the start and finish of this token is in the parse stream instead of just eat it.
	//likely we need a x3:variant ast or I would even be happy with a semantic action that puts these positions in an global vector or map
	//I am not not clear how I can obtain these locations.
	auto const eat_escape = x3::rule<struct crap>() = sy;




	auto green_test = x3::rule<struct asd>() = x3::string(GREEN_DEF);

	auto  clean_string = x3::rule<struct nonsense1, vector<std::string>>("clean_string");
	auto  clean_string_def = x3::rule<struct nonsense1, vector<std::string>>() =
		-all_but_magic_token % eat_escape;

	BOOST_SPIRIT_DEFINE(clean_string); //this will fail.  But if I define this outside of the scope, clean_string doesn't exist.  I can make clean_string static but it starts to get really messy. 
								//is there a better way?

}
#endif

namespace Magic
{
	namespace Parsers
	{

		namespace ANSI
		{

			void strip_codes_from_string(std::string & stripMe)
			{


				std::stringstream ss;
				int p = 0;

				vector<string> vs;

				auto f = stripMe.begin(), l = stripMe.end();

				p = x3::parse(f, l, clean_string, vs);


				for (auto vv : vs)
				{
					ss << vv;
				}

				if (!p)
				{
					throw std::exception("bad parse in:" __FUNCTION__);
				}

				stripMe = ss.str();


			}
		}
	}

}


#define CONSOLE_ANSI_MODE_ENABLE \
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);\
	DWORD dwMode = 0;\
	GetConsoleMode(hOut, &dwMode);\
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;\
	SetConsoleMode(hOut, dwMode);

int main()
{
	using namespace std;

#ifdef _WIN32
	CONSOLE_ANSI_MODE_ENABLE
#endif


	stringstream ss;
	ss<< GREEN_DEF << "test" << RESET_DEF;
	string newS = ss.str();

	cout << newS<<endl; //prints with ANSI codes for color
	
	Magic::Parsers::ANSI::strip_codes_from_string(newS);

	cout << newS << endl; //cleaned/stripped of ansi codes

	return 0;
}