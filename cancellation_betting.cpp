//
//  cancellation system analyzer
//  10/19/1998
//

#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

void tenbet();

int main()
{
  char ch;

  do
  {
      tenbet();

      cerr << "Play again? ";
      cin >> ch;
  }
  while ((ch == 'y') || (ch == 'Y'));

  return 0;
}

void tenbet()
{
  int maxloss, num, bet[1000], lpt, rpt, i, j, curbet, bank, result[2], randwin, g;

  long totbet, spins;

  cerr << "Enter maximum loss ";        cin  >> maxloss;
  cerr << "Enter number of trials ";    cin  >> num;
  cerr << "Roulette(1) or craps(2)? ";  cin  >> g;

  result[0] = 0;
  result[1] = 0;
  totbet    = 0;
  spins     = 0;

  if (g == 1)
  {
      randwin = 32767 * 18/38;
  }
  else
  {
      randwin = 32767 * 244 / 495;
  }

  for (i = 1; i <= num; i++)
  {
      bank =  0;
      lpt  =  1;
      rpt  = 10;

      for (j = 1; j <= 10; j++)
      {
          bet[j] = 1;
      }

      do
      {
          if (rpt == lpt)
          {
              curbet = bet[rpt];
          }
          else
          {
              curbet = bet[lpt] + bet[rpt];
          }

          while ((maxloss+bank < curbet)&&(maxloss+bank > 0))
          {
              spins++;

              if (maxloss + bank >= bet[lpt])
              {
                  totbet += bet[lpt];

                  if (rand() <= randwin)
                  {
                      bank += bet[lpt];
                      lpt++;
                  }
                  else
                  {
                      bank     -= bet[lpt];
                      bet[lpt] *= 2;
                  }
              }
              else
              {
                  totbet += (maxloss + bank);

                  if (rand() <= randwin)
                  {
                      bet[lpt] -= (maxloss + bank);
                      bank     += (maxloss + bank);
                  }
                  else
                  {
                      bank     -= (maxloss + bank);
                  }
              }

              if (rpt == lpt)
              {
                  curbet = bet[rpt];
              }
              else
              {
                  curbet = bet[lpt] + bet[rpt];
              }
          }

          if (maxloss + bank > 0)
          {
              totbet+=curbet;
              spins++;

              if (rand() <= randwin)
              {
                  lpt++;
                  rpt--;
                  bank     += curbet;
              }
              else
              {
                  rpt++;
                  bet[rpt]  = curbet;
                  bank     -= curbet;
              }
          }
      }
      while ((lpt <= rpt) && (maxloss + bank > 0));

      if (maxloss + bank == 0)
      {
          result[1]++;
      }
      else
      {
          result[0]++;
      }

      if (i % 100000 == 0)
      {
          cerr << i << "\n";
      }
  }

  cerr << "Maximum loss: "        << maxloss << "\n";
  cerr << "Probability of loss: " << (float)(result[1])/(float)(num) << "\n";
  cerr << "Average spins: "       << (float)(spins)/(float)(num) << "\n";
  cerr << "Average bet: "         << (float)(totbet)/(float)(num)<<"\n";
  cerr << "Wins: "                << result[0]<<"\nLosses: "<<result[1]<<"\n";
  cerr << "Total bet: "           << totbet<<"\n";
  cerr << "Total win/loss: "      << (result[0]*10)-(result[1]*maxloss) << "\n";
  cerr << "Total spins: "         << spins << "\n";
  cerr << "Net loss: "            << (float)((result[0]*10)-(result[1]*maxloss))/(float)totbet << "\n";
}
