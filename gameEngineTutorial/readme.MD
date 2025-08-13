# __*[ROSE ENGINE]*__... 
__how rose works__...
rose is the engine
sandbox is the game that depends on the engine...
when compiled, a ddl file rose.dll rose.dll.a is created and placed in same folder as .exe for sand box
all i can say thanks to cmake...
(ins)__[best_practice_refresh_on_libraries_in_Cpp_we_simplified_everything_by_using_macros]__
engineheaders.h is aheaderfile that contains all headers that we need from the engine 
we will include all headers here then include this header in our sandbox main file.
(__nb__)==> we specified to cmake to look for includes in the rose subfolder
============================================================================
now, chenye ni most important hapa ni, like libraries zenye zote tutatumia ku include kwa hii engine
tutazispecify peke kwa rose alafu during runtime tushikanishe hiyo dll yenye iko na kila kitu kwa sandbox.

hii ni best ju hatutashida tukilink ma library most.. hiyo inaconsume masaa viajab😂😂

[{a_bythe_way}]
[(ANYWAY)]__wacha-niadd-error-logging-na-ii-library-spdlog...aukitu-kama-io__
\\bytha leo nilifika cu, the 8th july 2025...:: haiwahusu lakini tulisoma kuhusu
the heart and all that we should feed it and how wes should guard it...
we kama uko intrested soma proverbs 4:23
                           luke 6:45
                           jeremiar(verse talking about how the heart is the greatest deceiver.)








PLEASE NOTE[FOR_EVERY_CPP_FILE_YOU_MAKE_ADD_IT_TO_cmake_LINK_LIBRARY_FUNCTION...]]..."({EWE})"