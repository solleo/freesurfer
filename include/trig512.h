/**
 * @file  trig512.h
 * @brief REPLACE_WITH_ONE_LINE_SHORT_DESCRIPTION
 *
 * REPLACE_WITH_LONG_DESCRIPTION_OR_REFERENCE
 */
/*
 * Original Author: REPLACE_WITH_FULL_NAME_OF_CREATING_AUTHOR 
 * CVS Revision Info:
 *    $Author: nicks $
 *    $Date: 2011/03/02 00:04:10 $
 *    $Revision: 1.3 $
 *
 * Copyright © 2011 The General Hospital Corporation (Boston, MA) "MGH"
 *
 * Terms and conditions for use, reproduction, distribution and contribution
 * are found in the 'FreeSurfer Software License Agreement' contained
 * in the file 'LICENSE' found in the FreeSurfer distribution, and here:
 *
 * https://surfer.nmr.mgh.harvard.edu/fswiki/FreeSurferSoftwareLicense
 *
 * Reporting: freesurfer@nmr.mgh.harvard.edu
 *
 */


#define PI ((double)3.14159265358979324)
#define COS(index) (_cosine[(index) & 511])
#define SIN(index) (_cosine[((index)+128) & 511])
#define TAN(index) (SIN(index)/COS(index))
double _cosine[512] = {
                        1.00000000000000000,
                        0.99992470183914454,
                        0.99969881869620422,
                        0.99932238458834950,
                        0.99879545620517239,
                        0.99811811290014921,
                        0.99729045667869022,
                        0.99631261218277802,
                        0.99518472667219689,
                        0.99390697000235605,
                        0.99247953459870999,
                        0.99090263542778002,
                        0.98917650996478097,
                        0.98730141815785838,
                        0.98527764238894125,
                        0.98310548743121633,
                        0.98078528040323044,
                        0.97831737071962763,
                        0.97570213003852854,
                        0.97293995220556015,
                        0.97003125319454399,
                        0.96697647104485211,
                        0.96377606579543987,
                        0.96043051941556581,
                        0.95694033573220887,
                        0.95330604035419383,
                        0.94952818059303666,
                        0.94560732538052132,
                        0.94154406518302078,
                        0.93733901191257492,
                        0.93299279883473889,
                        0.92850608047321556,
                        0.92387953251128675,
                        0.91911385169005774,
                        0.91420975570353065,
                        0.90916798309052238,
                        0.90398929312344334,
                        0.89867446569395384,
                        0.89322430119551532,
                        0.88763962040285395,
                        0.88192126434835504,
                        0.87607009419540662,
                        0.87008699110871142,
                        0.86397285612158674,
                        0.85772861000027208,
                        0.85135519310526514,
                        0.84485356524970708,
                        0.83822470555483805,
                        0.83146961230254524,
                        0.82458930278502526,
                        0.81758481315158370,
                        0.81045719825259480,
                        0.80320753148064492,
                        0.79583690460888354,
                        0.78834642762660626,
                        0.78073722857209447,
                        0.77301045336273697,
                        0.76516726562245893,
                        0.75720884650648455,
                        0.74913639452345933,
                        0.74095112535495909,
                        0.73265427167241284,
                        0.72424708295146692,
                        0.71573082528381865,
                        0.70710678118654753,
                        0.69837624940897286,
                        0.68954054473706693,
                        0.68060099779545305,
                        0.67155895484701840,
                        0.66241577759017177,
                        0.65317284295377677,
                        0.64383154288979147,
                        0.63439328416364550,
                        0.62485948814238639,
                        0.61523159058062685,
                        0.60551104140432552,
                        0.59569930449243336,
                        0.58579785745643886,
                        0.57580819141784531,
                        0.56573181078361320,
                        0.55557023301960222,
                        0.54532498842204642,
                        0.53499761988709722,
                        0.52458968267846891,
                        0.51410274419322173,
                        0.50353838372571756,
                        0.49289819222978405,
                        0.48218377207912275,
                        0.47139673682599766,
                        0.46053871095824003,
                        0.44961132965460662,
                        0.43861623853852764,
                        0.42755509343028211,
                        0.41642956009763719,
                        0.40524131400498989,
                        0.39399204006104811,
                        0.38268343236508976,
                        0.37131719395183755,
                        0.35989503653498814,
                        0.34841868024943457,
                        0.33688985339222004,
                        0.32531029216226294,
                        0.31368174039889147,
                        0.30200594931922808,
                        0.29028467725446236,
                        0.27851968938505312,
                        0.26671275747489838,
                        0.25486565960451458,
                        0.24298017990326388,
                        0.23105810828067113,
                        0.21910124015686979,
                        0.20711137619221856,
                        0.19509032201612827,
                        0.18303988795514097,
                        0.17096188876030122,
                        0.15885814333386146,
                        0.14673047445536175,
                        0.13458070850712620,
                        0.12241067519921620,
                        0.11022220729388307,
                        0.09801714032956060,
                        0.08579731234443991,
                        0.07356456359966743,
                        0.06132073630220859,
                        0.04906767432741802,
                        0.03680722294135885,
                        0.02454122852291229,
                        0.01227153828571995,
                        0.00000000000000001,
                        -0.01227153828571993,
                        -0.02454122852291228,
                        -0.03680722294135884,
                        -0.04906767432741801,
                        -0.06132073630220858,
                        -0.07356456359966741,
                        -0.08579731234443990,
                        -0.09801714032956059,
                        -0.11022220729388306,
                        -0.12241067519921619,
                        -0.13458070850712619,
                        -0.14673047445536174,
                        -0.15885814333386144,
                        -0.17096188876030121,
                        -0.18303988795514096,
                        -0.19509032201612826,
                        -0.20711137619221855,
                        -0.21910124015686978,
                        -0.23105810828067112,
                        -0.24298017990326387,
                        -0.25486565960451457,
                        -0.26671275747489837,
                        -0.27851968938505310,
                        -0.29028467725446235,
                        -0.30200594931922806,
                        -0.31368174039889146,
                        -0.32531029216226293,
                        -0.33688985339222003,
                        -0.34841868024943456,
                        -0.35989503653498813,
                        -0.37131719395183754,
                        -0.38268343236508977,
                        -0.39399204006104810,
                        -0.40524131400498987,
                        -0.41642956009763720,
                        -0.42755509343028207,
                        -0.43861623853852763,
                        -0.44961132965460660,
                        -0.46053871095824004,
                        -0.47139673682599763,
                        -0.48218377207912274,
                        -0.49289819222978404,
                        -0.50353838372571758,
                        -0.51410274419322170,
                        -0.52458968267846889,
                        -0.53499761988709721,
                        -0.54532498842204644,
                        -0.55557023301960221,
                        -0.56573181078361319,
                        -0.57580819141784530,
                        -0.58579785745643886,
                        -0.59569930449243332,
                        -0.60551104140432550,
                        -0.61523159058062685,
                        -0.62485948814238639,
                        -0.63439328416364547,
                        -0.64383154288979146,
                        -0.65317284295377676,
                        -0.66241577759017177,
                        -0.67155895484701837,
                        -0.68060099779545304,
                        -0.68954054473706693,
                        -0.69837624940897286,
                        -0.70710678118654754,
                        -0.71573082528381864,
                        -0.72424708295146691,
                        -0.73265427167241284,
                        -0.74095112535495911,
                        -0.74913639452345931,
                        -0.75720884650648454,
                        -0.76516726562245893,
                        -0.77301045336273697,
                        -0.78073722857209446,
                        -0.78834642762660626,
                        -0.79583690460888354,
                        -0.80320753148064492,
                        -0.81045719825259477,
                        -0.81758481315158368,
                        -0.82458930278502526,
                        -0.83146961230254524,
                        -0.83822470555483802,
                        -0.84485356524970706,
                        -0.85135519310526514,
                        -0.85772861000027208,
                        -0.86397285612158672,
                        -0.87008699110871141,
                        -0.87607009419540660,
                        -0.88192126434835504,
                        -0.88763962040285393,
                        -0.89322430119551531,
                        -0.89867446569395384,
                        -0.90398929312344334,
                        -0.90916798309052237,
                        -0.91420975570353065,
                        -0.91911385169005774,
                        -0.92387953251128677,
                        -0.92850608047321558,
                        -0.93299279883473887,
                        -0.93733901191257492,
                        -0.94154406518302078,
                        -0.94560732538052134,
                        -0.94952818059303666,
                        -0.95330604035419383,
                        -0.95694033573220887,
                        -0.96043051941556581,
                        -0.96377606579543985,
                        -0.96697647104485211,
                        -0.97003125319454399,
                        -0.97293995220556015,
                        -0.97570213003852854,
                        -0.97831737071962763,
                        -0.98078528040323044,
                        -0.98310548743121633,
                        -0.98527764238894124,
                        -0.98730141815785838,
                        -0.98917650996478097,
                        -0.99090263542778002,
                        -0.99247953459870999,
                        -0.99390697000235603,
                        -0.99518472667219689,
                        -0.99631261218277802,
                        -0.99729045667869021,
                        -0.99811811290014921,
                        -0.99879545620517239,
                        -0.99932238458834950,
                        -0.99969881869620422,
                        -0.99992470183914454,
                        -1.00000000000000000,
                        -0.99992470183914454,
                        -0.99969881869620422,
                        -0.99932238458834950,
                        -0.99879545620517239,
                        -0.99811811290014921,
                        -0.99729045667869022,
                        -0.99631261218277802,
                        -0.99518472667219689,
                        -0.99390697000235605,
                        -0.99247953459870999,
                        -0.99090263542778002,
                        -0.98917650996478097,
                        -0.98730141815785838,
                        -0.98527764238894125,
                        -0.98310548743121633,
                        -0.98078528040323046,
                        -0.97831737071962764,
                        -0.97570213003852854,
                        -0.97293995220556015,
                        -0.97003125319454400,
                        -0.96697647104485211,
                        -0.96377606579543987,
                        -0.96043051941556583,
                        -0.95694033573220887,
                        -0.95330604035419383,
                        -0.94952818059303666,
                        -0.94560732538052134,
                        -0.94154406518302079,
                        -0.93733901191257493,
                        -0.93299279883473889,
                        -0.92850608047321558,
                        -0.92387953251128677,
                        -0.91911385169005776,
                        -0.91420975570353065,
                        -0.90916798309052237,
                        -0.90398929312344335,
                        -0.89867446569395384,
                        -0.89322430119551532,
                        -0.88763962040285395,
                        -0.88192126434835505,
                        -0.87607009419540662,
                        -0.87008699110871142,
                        -0.86397285612158674,
                        -0.85772861000027209,
                        -0.85135519310526515,
                        -0.84485356524970708,
                        -0.83822470555483804,
                        -0.83146961230254525,
                        -0.82458930278502528,
                        -0.81758481315158370,
                        -0.81045719825259478,
                        -0.80320753148064493,
                        -0.79583690460888355,
                        -0.78834642762660627,
                        -0.78073722857209447,
                        -0.77301045336273698,
                        -0.76516726562245894,
                        -0.75720884650648455,
                        -0.74913639452345933,
                        -0.74095112535495912,
                        -0.73265427167241286,
                        -0.72424708295146693,
                        -0.71573082528381865,
                        -0.70710678118654752,
                        -0.69837624940897287,
                        -0.68954054473706694,
                        -0.68060099779545305,
                        -0.67155895484701839,
                        -0.66241577759017178,
                        -0.65317284295377674,
                        -0.64383154288979147,
                        -0.63439328416364553,
                        -0.62485948814238636,
                        -0.61523159058062686,
                        -0.60551104140432556,
                        -0.59569930449243334,
                        -0.58579785745643889,
                        -0.57580819141784527,
                        -0.56573181078361320,
                        -0.55557023301960226,
                        -0.54532498842204641,
                        -0.53499761988709724,
                        -0.52458968267846896,
                        -0.51410274419322172,
                        -0.50353838372571759,
                        -0.49289819222978401,
                        -0.48218377207912276,
                        -0.47139673682599770,
                        -0.46053871095824001,
                        -0.44961132965460662,
                        -0.43861623853852770,
                        -0.42755509343028209,
                        -0.41642956009763722,
                        -0.40524131400498985,
                        -0.39399204006104812,
                        -0.38268343236508982,
                        -0.37131719395183754,
                        -0.35989503653498818,
                        -0.34841868024943453,
                        -0.33688985339222005,
                        -0.32531029216226297,
                        -0.31368174039889146,
                        -0.30200594931922808,
                        -0.29028467725446243,
                        -0.27851968938505309,
                        -0.26671275747489842,
                        -0.25486565960451454,
                        -0.24298017990326390,
                        -0.23105810828067117,
                        -0.21910124015686978,
                        -0.20711137619221857,
                        -0.19509032201612833,
                        -0.18303988795514095,
                        -0.17096188876030127,
                        -0.15885814333386141,
                        -0.14673047445536176,
                        -0.13458070850712624,
                        -0.12241067519921618,
                        -0.11022220729388309,
                        -0.09801714032956067,
                        -0.08579731234443989,
                        -0.07356456359966747,
                        -0.06132073630220855,
                        -0.04906767432741803,
                        -0.03680722294135889,
                        -0.02454122852291228,
                        -0.01227153828571996,
                        0.00000000000000004,
                        0.01227153828571992,
                        0.02454122852291224,
                        0.03680722294135886,
                        0.04906767432741799,
                        0.06132073630220852,
                        0.07356456359966743,
                        0.08579731234443986,
                        0.09801714032956064,
                        0.11022220729388305,
                        0.12241067519921615,
                        0.13458070850712621,
                        0.14673047445536173,
                        0.15885814333386138,
                        0.17096188876030123,
                        0.18303988795514092,
                        0.19509032201612830,
                        0.20711137619221854,
                        0.21910124015686975,
                        0.23105810828067113,
                        0.24298017990326386,
                        0.25486565960451450,
                        0.26671275747489839,
                        0.27851968938505307,
                        0.29028467725446239,
                        0.30200594931922805,
                        0.31368174039889142,
                        0.32531029216226295,
                        0.33688985339222002,
                        0.34841868024943450,
                        0.35989503653498815,
                        0.37131719395183750,
                        0.38268343236508980,
                        0.39399204006104809,
                        0.40524131400498981,
                        0.41642956009763719,
                        0.42755509343028206,
                        0.43861623853852767,
                        0.44961132965460660,
                        0.46053871095823998,
                        0.47139673682599766,
                        0.48218377207912273,
                        0.49289819222978398,
                        0.50353838372571756,
                        0.51410274419322169,
                        0.52458968267846894,
                        0.53499761988709719,
                        0.54532498842204638,
                        0.55557023301960223,
                        0.56573181078361318,
                        0.57580819141784524,
                        0.58579785745643886,
                        0.59569930449243332,
                        0.60551104140432553,
                        0.61523159058062683,
                        0.62485948814238633,
                        0.63439328416364550,
                        0.64383154288979144,
                        0.65317284295377671,
                        0.66241577759017176,
                        0.67155895484701837,
                        0.68060099779545306,
                        0.68954054473706691,
                        0.69837624940897280,
                        0.70710678118654753,
                        0.71573082528381862,
                        0.72424708295146695,
                        0.73265427167241283,
                        0.74095112535495906,
                        0.74913639452345934,
                        0.75720884650648453,
                        0.76516726562245889,
                        0.77301045336273697,
                        0.78073722857209446,
                        0.78834642762660628,
                        0.79583690460888352,
                        0.80320753148064487,
                        0.81045719825259480,
                        0.81758481315158368,
                        0.82458930278502522,
                        0.83146961230254524,
                        0.83822470555483802,
                        0.84485356524970709,
                        0.85135519310526514,
                        0.85772861000027203,
                        0.86397285612158674,
                        0.87008699110871141,
                        0.87607009419540657,
                        0.88192126434835502,
                        0.88763962040285392,
                        0.89322430119551532,
                        0.89867446569395383,
                        0.90398929312344331,
                        0.90916798309052238,
                        0.91420975570353064,
                        0.91911385169005771,
                        0.92387953251128675,
                        0.92850608047321555,
                        0.93299279883473890,
                        0.93733901191257492,
                        0.94154406518302075,
                        0.94560732538052132,
                        0.94952818059303666,
                        0.95330604035419385,
                        0.95694033573220887,
                        0.96043051941556580,
                        0.96377606579543987,
                        0.96697647104485210,
                        0.97003125319454397,
                        0.97293995220556015,
                        0.97570213003852854,
                        0.97831737071962764,
                        0.98078528040323044,
                        0.98310548743121631,
                        0.98527764238894125,
                        0.98730141815785838,
                        0.98917650996478096,
                        0.99090263542778002,
                        0.99247953459870999,
                        0.99390697000235605,
                        0.99518472667219689,
                        0.99631261218277800,
                        0.99729045667869022,
                        0.99811811290014921,
                        0.99879545620517239,
                        0.99932238458834950,
                        0.99969881869620422,
                        0.99992470183914454
                      };
