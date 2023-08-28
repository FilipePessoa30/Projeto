#include "exam.h"
#include <cln/ffloat.h>
#include <cln/ffloat_io.h>

static div_test ffloat_div_tests[] = {

{ "0.73739415", "0.6416277",
  "1.1492554" },

{ "0.6736158", "-0.25522494",
  "-2.6393025" },

{ "-0.44216943", "0.31134832",
  "-1.420176" },

{ "-0.7041118", "-0.26929635",
  "2.6146355" },

{ "0.3573562", "0.73521775",
  "0.4860549" },

{ "-0.7661392", "0.77110463",
  "-0.9935606" },

{ "-0.91306114", "1.6586358E9",
  "-5.504892E-10" },

{ "-0.68994707", "4.0230333E8",
  "-1.7149921E-9" },

{ "0.28498656", "-7.617844E9",
  "-3.7410394E-11" },

{ "-0.72419757", "-9.226896E9",
  "7.848767E-11" },

{ "0.8352187", "8.3102536E9",
  "1.00504605E-10" },

{ "0.9707725", "3.3669448E9",
  "2.8832445E-10" },

{ "0.50785017", "6.048824E-11",
  "8.3958497E9" },

{ "-0.17675805", "4.1391092E-11",
  "-4.270437E9" },

{ "-0.42162335", "-4.4007357E-11",
  "9.580747E9" },

{ "-7.945299E-4", "-5.4965265E-11",
  "1.4455128E7" },

{ "-0.65178335", "-9.78151E-12",
  "6.6634228E10" },

{ "-0.6209788", "-3.8544803E-11",
  "1.611057E10" },

{ "0.94332725", "-4.9823833E19",
  "-1.8933253E-20" },

{ "0.30150706", "-4.9741757E19",
  "-6.061448E-21" },

{ "-0.8478371", "-9.85865E18",
  "8.5999306E-20" },

{ "-0.28524554", "3.1389898E19",
  "-9.087176E-21" },

{ "-0.5260848", "-7.936286E19",
  "6.6288534E-21" },

{ "-0.12941593", "-5.3575864E19",
  "2.415564E-21" },

{ "-0.20859545", "-9.867267E-21",
  "2.1140145E19" },

{ "0.35158414", "-8.2825064E-22",
  "-4.2449002E20" },

{ "-0.05635804", "-2.2999601E-21",
  "2.450392E19" },

{ "-0.003138721", "-3.3988403E-21",
  "9.234682E17" },

{ "-0.91386896", "-5.8199337E-21",
  "1.5702395E20" },

{ "-0.5374476", "2.256708E-21",
  "-2.3815556E20" },

{ "1.9669795E9", "-0.58137333",
  "-3.3833329E9" },

{ "-8.9879334E8", "0.35829848",
  "-2.5085046E9" },

{ "-9.057627E9", "0.4849478",
  "-1.867753E10" },

{ "3.687799E8", "-0.34055912",
  "-1.082866E9" },

{ "-5.1049994E9", "-0.16858816",
  "3.0280888E10" },

{ "-4.512774E9", "0.9385354",
  "-4.8083154E9" },

{ "-1.9312024E9", "-8.3940613E9",
  "0.2300677" },

{ "-8.2104387E9", "6.769607E9",
  "-1.2128383" },

{ "-6.9613486E9", "4.576518E9",
  "-1.5211015" },

{ "-1.486333E9", "1.2476433E9",
  "-1.1913126" },

{ "-7.653413E9", "5.167656E9",
  "-1.4810221" },

{ "-2.9815204E9", "8.942396E9",
  "-0.33341402" },

{ "9.304549E9", "-5.8002263E-11",
  "-1.60417E20" },

{ "-2.0750719E9", "1.272735E-11",
  "-1.6304037E20" },

{ "-1.1557549E9", "-7.2220556E-11",
  "1.6003129E19" },

{ "-3.3273495E9", "-9.9207274E-11",
  "3.353937E19" },

{ "-3.2167434E9", "7.7474506E-11",
  "-4.1520026E19" },

{ "4.4169416E9", "-4.638272E-11",
  "-9.5228166E19" },

{ "-3.732909E9", "-2.2763849E18",
  "1.6398409E-9" },

{ "-6.243126E9", "-4.1274483E19",
  "1.5125873E-10" },

{ "4.7162563E9", "-7.524631E19",
  "-6.267758E-11" },

{ "-1.3657349E9", "7.728982E19",
  "-1.7670308E-11" },

{ "-4.6216906E8", "-7.972877E19",
  "5.7967663E-12" },

{ "4.4542986E9", "3.1531836E19",
  "1.4126353E-10" },

{ "1.4738977E9", "-9.8130876E-21",
  "-1.5019714E29" },

{ "-5.918336E9", "2.9877495E-21",
  "-1.9808676E30" },

{ "-3.7166292E9", "-1.0826009E-21",
  "3.433056E30" },

{ "7.390683E9", "-2.1678685E-22",
  "-3.4091935E31" },

{ "6.2302886E8", "8.9466635E-21",
  "6.963812E28" },

{ "5.2357125E9", "4.854464E-22",
  "1.0785356E31" },

{ "-2.7721167E-11", "0.99550104",
  "-2.7846447E-11" },

{ "5.754337E-11", "-0.6344538",
  "-9.06975E-11" },

{ "-7.663363E-11", "0.020810604",
  "-3.6824317E-9" },

{ "3.2576632E-11", "0.6209498",
  "5.2462586E-11" },

{ "-9.507874E-11", "-0.19174337",
  "4.958645E-10" },

{ "-9.681176E-11", "-0.82680905",
  "1.1709084E-10" },

{ "6.458532E-11", "3.442031E8",
  "1.8763725E-19" },

{ "1.9113166E-11", "-7.0712125E9",
  "-2.7029546E-21" },

{ "-2.0099402E-12", "2.600844E9",
  "-7.7280303E-22" },

{ "-4.9634992E-12", "8.041176E9",
  "-6.1726036E-22" },

{ "3.2738747E-12", "7.299675E9",
  "4.484959E-22" },

{ "9.133733E-12", "-2.6318538E9",
  "-3.470456E-21" },

{ "-3.4146054E-11", "-1.5331155E-11",
  "2.227233" },

{ "6.06336E-11", "4.3750472E-11",
  "1.385896" },

{ "-4.229064E-11", "-9.169808E-11",
  "0.4611944" },

{ "6.166104E-11", "-3.5474658E-11",
  "-1.7381715" },

{ "-3.979801E-11", "-1.9510412E-11",
  "2.0398343" },

{ "9.726933E-11", "-5.6926824E-11",
  "-1.7086731" },

{ "8.041786E-11", "2.3718388E19",
  "3.3905282E-30" },

{ "-6.747094E-11", "-6.7324465E19",
  "1.0021756E-30" },

{ "-3.0713255E-11", "-4.8310887E19",
  "6.357419E-31" },

{ "-2.8496396E-11", "-4.9017306E19",
  "5.813538E-31" },

{ "-9.354275E-12", "-9.035095E19",
  "1.0353266E-31" },

{ "4.9274265E-12", "7.241873E19",
  "6.8040775E-32" },

{ "-4.377009E-11", "7.138917E-21",
  "-6.131195E9" },

{ "9.422678E-12", "-5.8862136E-21",
  "-1.6008046E9" },

{ "-6.83782E-11", "-3.6098812E-21",
  "1.8941952E10" },

{ "-8.1755075E-11", "-6.8725736E-21",
  "1.1895846E10" },

{ "-6.360949E-11", "4.2976342E-21",
  "-1.4801049E10" },

{ "3.3879413E-11", "-1.7169743E-21",
  "-1.9732044E10" },

{ "-9.948093E18", "-0.8695114",
  "1.1441014E19" },

{ "6.2748975E19", "-0.94829553",
  "-6.6170272E19" },

{ "-6.204444E18", "0.6874813",
  "-9.0248915E18" },

{ "6.7599936E19", "-0.45808762",
  "-1.4756988E20" },

{ "7.624068E19", "0.008471012",
  "9.0001855E21" },

{ "8.342225E19", "-0.3031574",
  "-2.7517803E20" },

{ "-6.3366795E19", "-1.4882481E9",
  "4.2578113E10" },

{ "-1.7335874E19", "-7.42875E9",
  "2.3336195E9" },

{ "-8.662651E19", "1.0327226E9",
  "-8.388168E10" },

{ "-4.9590965E19", "8.334462E9",
  "-5.95011E9" },

{ "8.191562E18", "5.930472E9",
  "1.3812664E9" },

{ "-3.5910857E19", "-7.342098E9",
  "4.8910894E9" },

{ "-3.6083056E19", "5.7372277E-11",
  "-6.2892843E29" },

{ "2.2896613E19", "-4.541202E-11",
  "-5.0419717E29" },

{ "6.1438805E19", "8.512014E-11",
  "7.217893E29" },

{ "6.3211746E19", "-6.185377E-12",
  "-1.0219547E31" },

{ "4.5452835E18", "2.0429606E-11",
  "2.2248514E29" },

{ "9.226608E19", "1.3297486E-11",
  "6.9386104E30" },

{ "1.8852943E19", "-1.623413E19",
  "-1.1613153" },

{ "-3.117305E18", "-9.5760065E19",
  "0.03255329" },

{ "-7.719376E19", "3.3627052E19",
  "-2.295585" },

{ "3.1309093E19", "-7.820006E19",
  "-0.4003717" },

{ "3.941958E19", "-9.51598E19",
  "-0.41424614" },

{ "-3.6364467E19", "-1.0757047E19",
  "3.380525" },

{ "2.906561E17", "-8.595159E-21",
  "-3.3816258E37" },

{ "-7.826226E-21", "-0.21695328",
  "3.6073327E-20" },

{ "-1.888169E-21", "0.5031878",
  "-3.7524144E-21" },

{ "8.304594E-21", "-0.3528648",
  "-2.3534775E-20" },

{ "-8.441606E-21", "-0.3639353",
  "2.3195348E-20" },

{ "-7.815205E-21", "0.38263506",
  "-2.0424697E-20" },

{ "-3.2837188E-21", "0.46961308",
  "-6.992392E-21" },

{ "-5.1739832E-21", "-3.8917279E9",
  "1.3294822E-30" },

{ "-5.3318596E-21", "-7.1995423E9",
  "7.405831E-31" },

{ "-7.4979364E-22", "9.148773E9",
  "-8.195565E-32" },

{ "4.6800053E-21", "3.9532006E8",
  "1.1838522E-29" },

{ "4.914653E-22", "-2.414465E9",
  "-2.035504E-31" },

{ "5.4722133E-21", "-9.977777E9",
  "-5.484401E-31" },

{ "9.815656E-21", "6.059642E-11",
  "1.619841E-10" },

{ "7.660357E-21", "9.7074675E-11",
  "7.891201E-11" },

{ "9.77743E-21", "2.5170428E-11",
  "3.8844908E-10" },

{ "8.818017E-21", "1.18070545E-11",
  "7.468431E-10" },

{ "5.445426E-21", "9.6208916E-11",
  "5.6600016E-11" },

{ "4.6823916E-21", "-1.9853067E-11",
  "-2.358523E-10" },

{ "9.347429E-21", "-7.285392E-22",
  "-12.830372" },

{ "-7.304412E-21", "6.766496E-21",
  "-1.079497" },

{ "-2.6850204E-21", "6.894023E-21",
  "-0.38947076" },

{ "-2.24644E-21", "-9.533858E-21",
  "0.23562758" },

{ "-8.525939E-21", "-9.961187E-22",
  "8.559159" },

{ "8.145676E-21", "4.304153E-22",
  "18.925154" },

};
