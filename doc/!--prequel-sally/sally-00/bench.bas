
1000 'benchmark
1010 '
1015 print "Benchmark... ";
1020 let A = .millis(10)
1030 for I = 1 to 8000
1040   let B = (I * I) / (I + I)
1041   let B = (I * I) / (I + I)
1042   let B = (I * I) / (I + I)
1043   let B = (I * I) / (I + I)
1044   let B = (I * I) / (I + I)
1045   let B = (I * I) / (I + I)
1046   let B = (I * I) / (I + I)
1047   let B = (I * I) / (I + I)
1048   let B = (I * I) / (I + I)
1049   let B = (I * I) / (I + I)
1080 next I
1090 let F = .millis(10)
1100 let G = F - A
1120 print "time: ";
1130 print G/100;
1140 print ",";
1150 print G%100

