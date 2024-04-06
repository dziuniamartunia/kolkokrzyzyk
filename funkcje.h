#pragma once

void logo();
void start();
void instrukcje();
void rysuj_plansze(char plansza[]);
bool czy_wygrana(char plansza[], char znak);
bool czy_remis(char p[]);
int wczytaj_pole(char plansza[], int pole);
int losuj_pole(char p[]);
int blok(char p[]);
int wygrana(char p[]);
void gra_na_dwoch_graczy(char plansza[]);
void gra_latwa1(char p[]);
void gra_latwa2(char p[]);
void gra_trudna1(char p[]);
void gra_trudna2(char p[]);