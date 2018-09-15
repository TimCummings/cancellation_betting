# cancellation_betting.rb

require 'pry'

# probably of winning craps = 244 / 495 = 49.292929293%
CRAPS_ODDS = 1..495
CRAPS_LOSS = 245

# i = round #; each round:
  # bank = 0
  # lptr = 0
  # rptr = 9
  # bet = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1] (size == 10)

def tenbet(results)
  totbet = 0
  rolls = 0
  maxloss = 15

  10.times do |round|
    bank = 0
    lptr = 0
    rptr = 9
    bet = Array.new(10, 1)

    while (lptr <= rptr) && (maxloss + bank > 0) do
      if rptr == lptr
        curbet = bet[rptr]
      else
        curbet = bet[lptr] + bet[rptr]
      end

      while (maxloss + bank < curbet) && (maxloss + bank > 0)
        rolls += 1 #rolls for craps, spins for roulette, etc.

        if maxloss + bank >= bet[lptr]
          totbet += bet[lptr]

          if rand(CRAPS_ODDS) < CRAPS_LOSS
            bank += bet[lptr]
            lptr += 1
          else
            bank -= bet[lptr]
            bet[lptr] *= 2
          end

        else
          totbet += (maxloss + bank)

          if rand(CRAPS_ODDS) < CRAPS_LOSS
            bet[lptr] -= (maxloss + bank)
            bank += (maxloss) + bank
          else
            bank -= maxloss + bank
          end
        end

        if rptr == lptr
          curbet = bet[rptr]
        else
          curbet = bet[lptr] + bet[rptr]
        end
      end

      if maxloss + bank > 0
        totbet += curbet
        rolls += 1

        if rand(CRAPS_ODDS) < CRAPS_LOSS
          lptr += 1
          rptr -= 1
          bank += curbet
        else
          rptr += 1
          bet[rptr] = curbet
          bank -= curbet
        end
      end
    end

    if (maxloss + bank) == 0
      results[:loss] += 1
    else
      results[:win] += 1
    end
  end
end

# binding.pry

results = Hash.new(0)

10000.times { tenbet(results) }

puts results
