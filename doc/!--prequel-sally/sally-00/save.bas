1000 if L<>0 goto 1100
1001 print "LED PIN: ": input L
1002 goto 1100
1004 '
1005 'prog1
1010 .dwrite L, HIGH
1020 .delay 100
1030 .dwrite L, LOW
1040 .delay 100
1050 goto 1010
1060 end
1065 '
1070 'prog2
1100 for I = 1 to 1000
1110   print I," ";
1120 next I
1125 call 2000
1130 end
1135 '
1140 'prog3
1200 for J = 1 to 1000
1210   .dwrite 13, HIGH
1215   .delay 10
1220   print J," ";
1230   .dwrite 13, LO
1235   .delay 10
1240 next J
1250 end
2000 '
2001 'procedure
2004 print ""
2005 print "this is call to subroutine"
2009 for K = 1 to 10
2010   .dwrite L, 1
2020   .delay 50
2030   .dwrite L,0
2040   .delay 50
2050 next K
2060 return
2100 '
2110 'procedure for downto
2120 for N = 20 to 0 step -1
2130   print N," ";
2140 next N
2150 return
