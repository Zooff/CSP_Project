%{
#include "arbre.h"
#include "y.tab.h"
int num_ligne=1;
%}
%option nounput noinput noyywrap
%%
","       {return(VIRGULE);}
".."      {;return(POINT_POINT);}
":"       {return(DEUX_POINTS);}
"("       {return(PO);}
")"       {return(PF);}
"["       {return(CO);}
"]"       {return(CF);}
"{"       {return(AO);}
"}"       {return(AF);}
"+"       {return(PLUS);}
"-"       {return(MOINS);}
"*"       {return(MULTIPLIE_PAR);}
"/"       {return(DIVISE_PAR);}
"%"       {return(MODULO);}
"="       {return(EGAL);}
"!="      {return(DIFFERENT);}
">="      {return(SUPERIEUR_OU_EGAL);}
"<="      {return(INFERIEUR_OU_EGAL);}
">"       {return(SUPERIEUR);}
"<"       {return(INFERIEUR);}
"&&"      {return(ET);}
"||"      {return(OU);}
"!"       {return(NON);}
"XD"      {return(XD);}
"C"       {return(C);}
"U"       {return(UNION);}
"ALLDIFF" {return(ALLDIFF);}
"SQRT"    {return(SQRT);}
"SIN"     {return(SIN);}
"COS"     {return(COS);}
"TAN"     {return(TAN);}
0.0|[0-9]+[.][0-9]+ {
yylval.valeur = atof(yytext);
                      return(REEL);}
0|[1-9][0-9]* {
yylval.valeur = atoi(yytext);
                      return(ENTIER);}
"TRUE"|"FALSE" {
if (strcmp("true", yytext)) yylval.valeur = 1;
else yylval.valeur = 0;
                      return(BOOLEEN);}
[a-z][a-z\_]*[0-9\_]* {yylval.chaine = strdup(yytext); return(IDF);}
[\n]                  num_ligne++;
[\t]                  ;
" "                   ;
.                     {return(ERREUR);}
%%
