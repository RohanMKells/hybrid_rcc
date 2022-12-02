// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "stats/distributions/multivariate/continuous/truncated_gaussian.h"

#include <cassert>
#include <iostream>

#include "testing/base/public/gmock.h"
#include "testing/base/public/gunit.h"
#include "third_party/eigen3/Eigen/Core"

class DistributionTest {
 public:
  Eigen::ArrayXd mu_, std_, a_, b_;
  Eigen::ArrayXXd x_, pdf_, cdf_;
  DistributionTest() = delete;
  DistributionTest(Eigen::ArrayXd mu, Eigen::ArrayXd std, Eigen::ArrayXd a,
                   Eigen::ArrayXd b, Eigen::ArrayXXd x, Eigen::ArrayXXd pdf,
                   Eigen::ArrayXXd cdf) {
    mu_ = mu;
    std_ = std;
    a_ = a;
    b_ = b;
    x_ = x;
    pdf_ = pdf;
    cdf_ = cdf;
  }
};

class TruncatedGaussianTest : public ::testing::Test {
 protected:
  std::vector<DistributionTest> tests;

  TruncatedGaussianTest() {}

  ~TruncatedGaussianTest() override {}

  void SetUp() override {
    tests = std::vector<DistributionTest>{
        DistributionTest(
            Eigen::ArrayXd{{-1.1212451885837726, 10.318989185531958,
                            -8.51660130434686, 1.553186966708795,
                            -8.979924709043194}},
            Eigen::ArrayXd{{0.32705571386556487, 0.22928324290718505,
                            0.005390132357975586, 0.5079120263734311,
                            0.821858710649148}},
            Eigen::ArrayXd{{-1.2464829765206873, 10.094238424760574,
                            -8.517659790677655, 1.3812957701107746,
                            -9.189651284931642}},
            Eigen::ArrayXd{{-0.8867700891746936, 10.4270691681374,
                            -8.512303991117426, 1.6745285479828367,
                            -8.926859053845671}},
            Eigen::ArrayXXd{
                {-1.228276483862181, 10.272839428018974, -8.515534762163176,
                 1.6325152268833047, -8.962480039089314},
                {-0.9331917989411627, 10.280925875894724, -8.516652089767524,
                 1.5102845532604787, -8.988303380534017},
                {-1.13085099851129, 10.226306948164536, -8.515498708910506,
                 1.5510458868955705, -8.990248384002662},
                {-1.0720372629044148, 10.412776818275795, -8.51506924527061,
                 1.5231451207576545, -9.108247411568872},
                {-0.9015393353991695, 10.273839978075074, -8.513251807056188,
                 1.4161562225925473, -9.102366377812025}},
            Eigen::ArrayXXd{
                {2.8035668670864746, 3.292707164472975, 198.74196796741265,
                 3.419884327376589, 3.837888931797003},
                {2.5071207743327597, 3.314102689285364, 202.66190556255756,
                 3.4495237335038675, 3.8385541035416892},
                {2.956510737828882, 3.096483935566321, 198.47466728300662,
                 3.4618209142755267, 3.8384507431904584},
                {2.9244966512081896, 3.0904194371970077, 194.6472592137773,
                 3.4558014005933235, 3.7922454749942496},
                {2.360336901626454, 3.2955691789886994, 167.08564868587928,
                 3.338126341666971, 3.796387652462806}},
            Eigen::ArrayXXd{
                {0.05055499265427734, 0.4958278768450399, 0.4279083342586583,
                 0.8574055459210814, 0.8633962405646578},
                {0.8886043455712411, 0.5225433642906216, 0.20286095633067067,
                 0.4355499492215579, 0.764272381223412},
                {0.333161736373573, 0.34671109179723586, 0.43506883573175026,
                 0.5764832369557908, 0.7568064772114574},
                {0.5065688346621188, 0.9564170481826253, 0.5195266253772765,
                 0.4799555093891845, 0.3058304448465206},
                {0.9656746352830783, 0.49912383200061095, 0.8507278990186624,
                 0.11520776644710619, 0.32814504164405733}}),
        DistributionTest(
            Eigen::ArrayXd{{2.057702423644283, 4.246657346444339,
                            -1.3190662855733422, 9.48865720025588,
                            9.787147787005267, 2.02120920977681}},
            Eigen::ArrayXd{{0.016374533806594482, 0.47158095427054225,
                            0.6619928291470969, 0.9631835161820732,
                            0.4742717558162286, 0.3070553892461634}},
            Eigen::ArrayXd{{2.052230953400393, 4.10778175545707,
                            -1.6329533100611433, 9.32686303019534,
                            9.388055133734289, 1.765087554740284}},
            Eigen::ArrayXd{{2.065092427068918, 4.63776171880094,
                            -0.6606212040648425, 10.176965746682168,
                            10.063739071554599, 2.2697749081532916}},
            Eigen::ArrayXXd{
                {2.0590816305028454, 4.22036235244003, -1.6314185286431244,
                 9.825583849970485, 9.521695738069885, 2.2055166967106437},
                {2.0610181180746436, 4.545560001288852, -1.3384587570008568,
                 9.58032456728006, 9.92917035325769, 1.866165430506855},
                {2.0587610956987907, 4.477517800718346, -1.2096486706253315,
                 9.42057963191731, 9.74452426165828, 1.8575530811190573},
                {2.057430931184204, 4.563304698665023, -1.0122357203561831,
                 9.914229465858261, 9.494584476475742, 1.9573589853339535},
                {2.0605318900402927, 4.189217289563318, -0.909692477989787,
                 9.360834427755254, 9.597779510432112, 2.051451486383242}},
            Eigen::ArrayXXd{
                {79.6023921701391, 2.0483700322676826, 1.0321719221396237,
                 1.183227058494026, 1.3828890632397883, 1.8428975367614588},
                {78.26418580175897, 1.678210441557021, 1.1532117974601235,
                 1.2521957057630797, 1.546467147726105, 1.942553350363442},
                {79.718473406258, 1.8198815086240026, 1.1380546875498576,
                 1.2547414604847051, 1.6108644630685673, 1.9144824629903199},
                {79.87428305322403, 1.63749922296682, 1.0362060787378582,
                 1.1408988349639362, 1.3371574242986883, 2.1594723728870417},
                {78.70148524696219, 2.036394638779914, 0.9529175436666748,
                 1.246851490134863, 1.493461038219503, 2.1959921289227617}},
            Eigen::ArrayXXd{
                {0.5391387052955193, 0.22692834548920476, 0.001583290714881268,
                 0.6178907589610405, 0.16882489222288152, 0.8894963086248537},
                {0.6921666464447512, 0.8553631923530133, 0.32663985350547414,
                 0.3176971739185015, 0.8030789194939026, 0.1778160074811548},
                {0.5136039532242538, 0.7362128078688485, 0.4746732862931427,
                 0.11700237152439145, 0.5079155118468653, 0.1612061418318636},
                {0.4074032882797703, 0.8847833173313471, 0.6907259819198185,
                 0.7209638865042912, 0.1319463796488741, 0.36606004314138524},
                {0.654003386227062, 0.16329527528116777, 0.7928559684581417,
                 0.042249563486265955, 0.27842758441111265,
                 0.5725744712931433}}),
        DistributionTest(
            Eigen::ArrayXd{{2.248673350177034, 8.05958740596817,
                            10.954435896047471, -8.386026244024746,
                            4.148270525700669, 1.9802590623942784,
                            1.1007380395897535, 10.992019325268718}},
            Eigen::ArrayXd{{0.3261222839073852, 0.4193118697867054,
                            0.9444872742323106, 0.6555854378748776,
                            0.20862353269131007, 0.6230126114609843,
                            0.4555514263082575, 0.605703198047976}},
            Eigen::ArrayXd{{1.956621640612979, 7.757262344543648,
                            10.142882876465038, -8.685226355396798,
                            4.078155796532957, 1.4691297825385579,
                            0.9647117362309524, 10.951263537551721}},
            Eigen::ArrayXd{{2.4986062812269565, 8.395419779585527,
                            11.378896207602596, -8.34520441877136,
                            4.2272664363050945, 2.4270398786186007,
                            1.541425449016601, 11.105963820320568}},
            Eigen::ArrayXXd{
                {2.0698610171557092, 8.08381975609598, 10.91260987250586,
                 -8.447206859017731, 4.079537982661688, 2.3529852778210496,
                 1.0843350994401497, 11.03561224131741},
                {2.27894182745674, 7.865546314868165, 10.993372635904842,
                 -8.482470912377504, 4.222831803805328, 2.086212675745976,
                 1.2996359554332197, 11.022470870451357},
                {2.402570722152698, 7.9784296891678, 11.29808227216417,
                 -8.568424914961826, 4.220918913667994, 2.3250544063493215,
                 1.0897938559933071, 11.016451036300849},
                {2.004708056309704, 8.25745153407099, 10.94369327657343,
                 -8.585653054721659, 4.115900264769593, 1.5177890068643372,
                 1.5133541058835394, 11.035818765047184},
                {2.264427410582546, 7.773211504367239, 11.146554693577691,
                 -8.645901094847531, 4.099970434628661, 2.115743416824296,
                 1.0243003309786316, 11.060141303376229}},
            Eigen::ArrayXXd{
                {1.774915338557073, 1.7177413868320646, 0.8821852504907352,
                 3.017817071162733, 6.48905878351598, 0.9606240219979474,
                 1.9418086568551867, 6.476666975355038},
                {2.053942571795363, 1.5459001981664053, 0.8823006402672365,
                 2.9983653066964386, 6.427093985387046, 1.1323856440891253,
                 1.766418959138623, 6.48526152416436},
                {1.845449932737781, 1.6886838006915434, 0.8264928438714159,
                 2.915917006240815, 6.4479190843401115, 0.9857467752997798,
                 1.9425071869167774, 6.488182311524029},
                {1.5593312866480913, 1.5393275283888208, 0.8829935862829583,
                 2.893675934426124, 6.768984393348875, 0.8722091640507865,
                 1.2892695650885282, 6.4765076665050145},
                {2.060402825945648, 1.3626872124004272, 0.8649698658019848,
                 2.8019659623857534, 6.669789282329344, 1.1220328463300115,
                 1.9159068616329857, 6.452524424463393}},
            Eigen::ArrayXXd{
                {0.1795736646421328, 0.5200936723731527, 0.6005012957176996,
                 0.6911806682786006, 0.008959240049609435, 0.9314904003922915,
                 0.2285675398979763, 0.5472714079325214},
                {0.5931006313129363, 0.15609592552261056, 0.6717971055938843,
                 0.5850779692312938, 0.9716083251986826, 0.6486459932979892,
                 0.6349693924953358, 0.4620993246818931},
                {0.8368136592911359, 0.33964841547355284, 0.9343163713703834,
                 0.33055192396093674, 0.9592940069038866, 0.9043054407953908,
                 0.23916943392356213, 0.42305001379047846},
                {0.07074579374460145, 0.8066463592105362, 0.6279376535673196,
                 0.280505048809619, 0.25058082146740807, 0.04119287919623955,
                 0.964821871569933, 0.548608976915142},
                {0.5632370645917875, 0.021448710828806217, 0.8059116832829886,
                 0.10882345454776574, 0.14349205420376263, 0.6819393166738358,
                 0.11260301672216508, 0.7058633657005483}}),
        DistributionTest(
            Eigen::ArrayXd{{10.028194905934296, 6.760583492124887,
                            0.4453281730717311, 9.128434109325916,
                            -8.895374613936637, -7.202756688625617,
                            2.837164044714088}},
            Eigen::ArrayXd{{0.0934208539377066, 0.10501106385257153,
                            0.07819901166739751, 0.7208450216834517,
                            0.22960512996246696, 0.6202971380772655,
                            0.7610567702484462}},
            Eigen::ArrayXd{{9.983984581764087, 6.669638262763513,
                            0.3914555600867876, 9.020663068927297,
                            -9.073008427987657, -7.459401539528943,
                            2.307997843948312}},
            Eigen::ArrayXd{{10.105144543826766, 6.830506938971123,
                            0.4526004815924261, 9.692817246696583,
                            -8.790457299237278, -6.804715517155204,
                            3.592629342035306}},
            Eigen::ArrayXXd{
                {10.079198870971805, 6.796532648783529, 0.43727643041698294,
                 9.690628429290602, -9.027679192750675, -6.823771679932805,
                 3.4809525327948654},
                {10.040899729001207, 6.736114968052854, 0.44364468674511687,
                 9.135816222134213, -8.803048797381718, -7.059929902860324,
                 2.55323257348206},
                {10.020060002219923, 6.789806299025224, 0.4134352181150263,
                 9.582488173064979, -8.794978256486193, -7.205341802856166,
                 2.740236260699315},
                {10.019779341626291, 6.772843346415516, 0.39347638185149975,
                 9.147034380295693, -8.80742644674712, -6.8561239763537545,
                 2.4030536278980503},
                {10.030427054503521, 6.790022421507698, 0.39566932457952797,
                 9.505327846751952, -8.92296060985309, -7.2702231413502645,
                 2.8255677381917415}},
            Eigen::ArrayXXd{
                {7.714279114135378, 6.466953382408706, 17.40224000379328,
                 1.191809265335796, 3.223400646519693, 1.3343313491301565,
                 0.6148500588634646},
                {8.871654539009558, 6.673575500591518, 17.490678337481214,
                 1.615347324237794, 3.509980364494352, 1.5660644113447164,
                 0.8202186872518383},
                {8.920191528428886, 6.596779822506976, 16.098589569344664,
                 1.324746154255324, 3.458582331441235, 1.608120049678114,
                 0.8722301858588225},
                {8.917818021785417, 6.810648205162736, 14.042181071237621,
                 1.6148943309529045, 3.536350469925108, 1.3756635221118083,
                 0.7473120055658155},
                {8.95151919745332, 6.592988751522745, 14.300109547083153,
                 1.4090510047507718, 3.7781632662908367, 1.5986501650612301,
                 0.8792308539845789}},
            Eigen::ArrayXXd{
                {0.8165549657886557, 0.7954939789249094, 0.7323414859150323,
                 0.997394437561889, 0.13724297058724869, 0.974813852880939,
                 0.935649994903616},
                {0.49498034593253604, 0.3874340182562574, 0.8435061945986844,
                 0.18537547817120853, 0.9563095983265982, 0.628911491270016,
                 0.1863927220420735},
                {0.30882151337728586, 0.7515447816478962, 0.3300870762886018,
                 0.861195427130555, 0.9844320188140521, 0.39708319490514454,
                 0.34538828608512967},
                {0.30631829833452867, 0.6375920780672397, 0.028131889446597037,
                 0.20349452463361556, 0.9408860202617512, 0.9309700356563526,
                 0.06839023641711589},
                {0.40155502440602514, 0.7529700848754863, 0.05920957817523998,
                 0.7556578037400838, 0.509476512850975, 0.29295882841350773,
                 0.42019360179402465}}),
        DistributionTest(
            Eigen::ArrayXd{{-6.988950755642992, -0.22616267988146532,
                            7.483760305346397, -3.899337396057911,
                            -4.758641232473538, -2.5142253960582375}},
            Eigen::ArrayXd{{0.5147580866715535, 0.00587841687782209,
                            0.9986418538639001, 0.950512178744587,
                            0.37309217368405156, 0.8581380081531049}},
            Eigen::ArrayXd{{-7.445243927573331, -0.22957007028535895,
                            6.5509927397625916, -4.723707757787033,
                            -4.787557755675646, -2.6157875785782094}},
            Eigen::ArrayXd{{-6.837561154353323, -0.22424576194120188,
                            8.462387952538075, -3.268350986228025,
                            -4.625573523437835, -1.8143941082215003}},
            Eigen::ArrayXXd{
                {-6.9700298460592665, -0.2242980056951939, 7.29827551770527,
                 -3.945836686823881, -4.646437921170233, -2.1169739868313955},
                {-6.838116331025406, -0.22601591154628536, 7.922995546454684,
                 -4.228663023762867, -4.692257426877584, -2.141292703220184},
                {-6.989719126655002, -0.22829388783354929, 8.393692518312283,
                 -3.4336633741236455, -4.664888465812774, -2.028812024388531},
                {-7.059363349023589, -0.22829873528091704, 7.123197000952372,
                 -4.468642103839668, -4.6676777967836225, -2.031949073144665},
                {-7.392340447448501, -0.22743897906225774, 8.037356281683909,
                 -4.26011028742667, -4.737126978871495, -2.1901258698523653}},
            Eigen::ArrayXXd{
                {1.8096996989143879, 186.11808795362464, 0.593755842377716,
                 0.7570925742264637, 6.004162150893017, 1.2294163266019236},
                {1.734824209503096, 195.66025602912367, 0.548392330856765,
                 0.7138413878908314, 6.183259362171048, 1.2451508767241966},
                {1.8109206094343733, 183.2719188592411, 0.39885669651348227,
                 0.6722778990344972, 6.08667874570824, 1.1661446997983314},
                {1.7940596478926227, 183.21707314139562, 0.5659679462677654,
                 0.6335344985742368, 6.097953967394801, 1.168550797229207},
                {1.3321358118802418, 191.1620967292688, 0.5180470090239546,
                 0.7053193207234937, 6.2714791687262155, 1.2742629849831546}},
            Eigen::ArrayXXd{
                {0.7640031059276811, 0.9902903132222255, 0.3798295868549957,
                 0.5194039347079784, 0.8758387740966839, 0.6634764702822924},
                {0.9990370184279265, 0.660085700639268, 0.7482612044928971,
                 0.30991347260377794, 0.5962968953785602, 0.6333857130402335},
                {0.7283550567182963, 0.223200777646934, 0.9734619884489696,
                 0.8939905161932112, 0.7642764714905058, 0.7691434950816808},
                {0.6026312874959121, 0.2223125095534375, 0.27806728833098093,
                 0.14757378575719893, 0.7472829104899668, 0.7654814654975101},
                {0.06759472232400322, 0.3835128949175811, 0.8092907988841975,
                 0.287597344833291, 0.3165452825113485, 0.5718563703314595}}),
        DistributionTest(
            Eigen::ArrayXd{
                {0.031695923950481486, -5.41971061308247, -3.4801275864236736,
                 4.116405483549354, 3.3374192844056303, -1.4329580062926066,
                 8.728680745476353, 10.011638798098097, 2.611697637667687}},
            Eigen::ArrayXd{
                {0.118340092380676, 0.12389172661759484, 0.624283054202723,
                 0.3409781178589455, 0.19279890875867478, 0.9283839963929412,
                 0.7086649037929948, 0.7152093931863474, 0.795918400359173}},
            Eigen::ArrayXd{
                {-0.06014532908029918, -5.431901320926029, -3.641215708099142,
                 4.019065700406403, 3.154496806977713, -1.9744339942387918,
                 8.498093323084802, 9.728231594630083, 2.280039872883769}},
            Eigen::ArrayXd{
                {0.05283591123934206, -5.353378937396234, -3.312826847268613,
                 4.375266600707974, 3.4730236278979194, -1.1217273696379562,
                 9.022980034694232, 10.515770496539291, 2.667199417078615}},
            Eigen::ArrayXXd{
                {0.026379048697095862, -5.392539151111974, -3.434290450746044,
                 4.086165745073575, 3.2929460267880915, -1.9571350647167318,
                 8.893846753229408, 10.412055676138568, 2.661888407027308},
                {0.0436990077186148, -5.355337312944379, -3.314681177255657,
                 4.068965956099562, 3.2554282392981384, -1.4062462644304707,
                 8.894565514910898, 10.075089559404168, 2.639333760161033},
                {0.03973896809859999, -5.4275502122427435, -3.430891706481836,
                 4.193285525234317, 3.300615201418745, -1.5374066680026544,
                 8.633542616114063, 9.75494394691982, 2.3951341848488577},
                {0.030812602838855743, -5.3968025519384355, -3.513044790406574,
                 4.105119914668985, 3.4061198985187042, -1.8855429819488239,
                 8.646085775916696, 10.356489548271771, 2.343354814074825},
                {0.01758063081826642, -5.399229905832027, -3.389729435945989,
                 4.258340974828099, 3.213134407400176, -1.8047092306875727,
                 8.550946284168354, 9.8879707414107, 2.6330165234088883}},
            Eigen::ArrayXXd{
                {9.566447578649617, 12.936213537589701, 3.072063968134362,
                 2.9998703985747808, 3.4283618712800834, 1.0426534918125085,
                 1.8984309891179079, 1.1530160281840771, 2.641914971224256},
                {9.526975848567721, 11.57782780630073, 2.9740593806130664,
                 2.9826833763789793, 3.2163951105085458, 1.222317346656451,
                 1.8979813013701294, 1.343351028351877, 2.6455778146578734},
                {9.554015860642144, 13.224595406999917, 3.0707906910975744,
                 2.9361037891740898, 3.4572279359715368, 1.2151088450722365,
                 1.9331991613144972, 1.2645228256818937, 2.5509737351222834},
                {9.575841079679659, 13.02649946619875, 3.076076840730387,
                 3.01004160120446, 3.30422078618955, 1.0858200263646896,
                 1.9374947439422336, 1.2006460518056474, 2.500917603913611},
                {9.50822949625175, 13.071267574445232, 3.048230255318187,
                 2.76175267640377, 2.860253619816411, 1.128614791843302,
                 1.890302656058357, 1.3286366350922436, 2.6462236632854284}},
            Eigen::ArrayXXd{
                {0.7477349048082599, 0.5184659918148402, 0.6318247273834107,
                 0.1982702500755189, 0.40396824764431094, 0.017941206408194646,
                 0.7612898607782179, 0.8855339525692012, 0.9859718188039379},
                {0.9133787952317474, 0.9774200621016719, 0.9944872906832349,
                 0.14681014986885796, 0.2789683223388973, 0.6590891501685405,
                 0.7626542187295673, 0.45790579476340215, 0.9263390715492397},
                {0.8755945532185029, 0.0574659538128893, 0.6422637490374754,
                 0.5188157621035276, 0.4303749700509353, 0.49897657776103294,
                 0.25696409511340723, 0.033545216876777285, 0.2869111012097003},
                {0.7901740516814699, 0.46311602694192605, 0.38940705643327383,
                 0.2552413098127601, 0.7960301507550044, 0.09415944759535413,
                 0.2812400850056014, 0.8201180388622892, 0.1560773670079587},
                {0.6637830107959181, 0.43144078654471907, 0.768245211156631,
                 0.704659232293935, 0.15009736028663068, 0.1837053966395289,
                 0.09888824348628666, 0.20648789426153008, 0.909624202493309}}),
        DistributionTest(
            Eigen::ArrayXd{{4.721673401294883, -1.9109414808248886}},
            Eigen::ArrayXd{{0.015371589732514512, 0.7363334162192003}},
            Eigen::ArrayXd{{4.721228034117815, -2.1728816492555403}},
            Eigen::ArrayXd{{4.725907469547151, -1.585302640874448}},
            Eigen::ArrayXXd{{4.721804923833359, -1.6397995436995256},
                            {4.724850626877784, -1.6140508156562572},
                            {4.723001212128977, -2.113579806373816},
                            {4.725716700382871, -1.6735980114130982},
                            {4.723993316868819, -2.172762720327021}},
            Eigen::ArrayXXd{{216.14118323261994, 1.6340895568626097},
                            {211.58082619399826, 1.6121968090023224},
                            {215.34418311641426, 1.6837376724458384},
                            {208.79943594504667, 1.660194239211111},
                            {213.70138755179266, 1.6415926028351553}},
            Eigen::ArrayXXd{{0.12468037631069893, 0.9122293147725001},
                            {0.7781478596691402, 0.9540268126011715},
                            {0.38290083294139554, 0.09864431389244788},
                            {0.9602334704567485, 0.8565498325662264},
                            {5.958027599914656e-01, 1.952272424091827e-04}}),
        DistributionTest(
            Eigen::ArrayXd{{8.384799605831375, -2.7186510331534457,
                            -4.912979008946978, -4.14485863906318,
                            4.646858488766696}},
            Eigen::ArrayXd{{0.5471738853853595, 0.8645723585848046,
                            0.37625014262893364, 0.08185683337601868,
                            0.0928512612676945}},
            Eigen::ArrayXd{{8.004300168755123, -2.8622024735643574,
                            -4.962156218830086, -4.182598164575448,
                            4.569879758059016}},
            Eigen::ArrayXd{{8.63089162915864, -2.0803142230589415,
                            -4.648907281884145, -4.111089754898771,
                            4.698853171395793}},
            Eigen::ArrayXXd{
                {8.377339688395123, -2.5397762524130116, -4.769839822324039,
                 -4.133170919647927, 4.6136326661563904},
                {8.526688936231572, -2.1438466453474208, -4.7316345111303315,
                 -4.148209975296208, 4.6858354417952075},
                {8.557718311145218, -2.6791253128270256, -4.84908636481274,
                 -4.133893942371357, 4.669686168974795},
                {8.413797089286833, -2.8301086438265504, -4.848131970539932,
                 -4.1582140892794115, 4.640202715410834},
                {8.395523842962824, -2.5431928106526205, -4.938156846532146,
                 -4.173624576044489, 4.683934757469239}},
            Eigen::ArrayXXd{
                {1.6948245852515607, 1.3451201858047346, 3.175345687006284,
                 14.287974493688473, 7.922119808887437},
                {1.638941412267663, 1.1017261632372697, 3.039310579787336,
                 14.422270188370991, 7.733614341009325},
                {1.6124219933621688, 1.3727841335991084, 3.3647845155954776,
                 14.305447300806618, 8.194487242364907},
                {1.6926036205942492, 1.3628474037318152, 3.3633246262411554,
                 14.24351449361033, 8.424247152474443},
                {1.6946565856275386, 1.3462098801280589, 3.4060163091524234,
                 13.570040615070091, 7.798721121683423}},
            Eigen::ArrayXXd{
                {0.5838800764592378, 0.4404392452356381, 0.6444891829835041,
                 0.6941807619115639, 0.30802051238625555},
                {0.834355624736075, 0.9317476683236708, 0.7632886966275035,
                 0.4776865680316246, 0.9025457709670085},
                {0.8848119132699266, 0.25066661099295884, 0.3844605200476047,
                 0.6838438491440545, 0.77364344283385},
                {0.6456513303615651, 0.04362449536975803, 0.38767115613463277,
                 0.3341219318694377, 0.5266014763478465},
                {0.6147003376382154, 0.43584169654772703, 0.08151282837880093,
                 0.11921966486127783, 0.8877843086902054}}),
        DistributionTest(
            Eigen::ArrayXd{
                {-6.984972769188481, -1.1768370585085108, 3.1641916429334778}},
            Eigen::ArrayXd{
                {0.5944477127544467, 0.7130351484462017, 0.6184218964706596}},
            Eigen::ArrayXd{
                {-7.196838637507177, -1.4192071994710183, 3.1247570229573567}},
            Eigen::ArrayXd{
                {-6.772818309828333, -1.112794788763751, 3.337168120229609}},
            Eigen::ArrayXXd{
                {-6.786290263411139, -1.3341961512658458, 3.1425923414971515},
                {-6.8971155251657095, -1.2649595753473284, 3.28096003471234},
                {-6.909672643910071, -1.2773524619883603, 3.3245319636932686},
                {-6.778172849889593, -1.1133720060639982, 3.280838751246497},
                {-7.106059803584846, -1.1758333992555334, 3.3354623229958267}},
            Eigen::ArrayXXd{
                {2.2776400212848418, 3.2343931206554744, 4.755488343266435},
                {2.3823155211682963, 3.2889098906229597, 4.674318819816502},
                {2.3892317333479127, 3.281357187031212, 4.601111867641463},
                {2.267057075978012, 3.3010217426232487, 4.674491824534476},
                {2.3590255752681504, 3.3141201165525853, 4.579359935078177}},
            Eigen::ArrayXXd{
                {0.9694342693894998, 0.2707360552964977, 0.08476119993212554},
                {0.7105082317766562, 0.4967338943047484, 0.7398637733307166},
                {0.6805486959845636, 0.4560205998084816, 0.9420173932993243},
                {0.9878801155136535, 0.9980946619932619, 0.7392968452507366},
                {0.21004276426802826, 0.7913672815235663, 0.9921915332460618}}),
        DistributionTest(
            Eigen::ArrayXd{
                {-8.834980036782948, 2.6457636127831865, 1.491136010991406,
                 3.1065022916472493, 3.9215715757329015, 8.175525647314021,
                 -0.3010618470512618, 4.60556680997432, 9.787799877729093}},
            Eigen::ArrayXd{
                {0.29858552193378485, 0.9830545400919822, 0.49487640836478064,
                 0.8833630029935673, 0.08288965316199182, 0.7161190786217156,
                 0.6065532720267163, 0.6366410549243691, 0.8215763967825436}},
            Eigen::ArrayXd{
                {-8.892199361358758, 2.1225723961176977, 1.3052158775107536,
                 2.9671576472475887, 3.87286029723871, 7.716159119080051,
                 -0.468923768567558, 4.539836009377803, 9.351607402920964}},
            Eigen::ArrayXd{
                {-8.758933410628154, 3.378307639719105, 1.7050607812350633,
                 3.8068026637844494, 3.9490156955115046, 8.18365981540638,
                 0.04106273318895126, 5.2289727326058975, 9.905261536711247}},
            Eigen::ArrayXXd{
                {-8.843318833425228, 3.2956467584638687, 1.3970866705400464,
                 3.6963926912790694, 3.8955974513711107, 7.825504740586116,
                 -0.43288334968664594, 4.571161445312932, 9.80884622761524},
                {-8.844845370499451, 3.169673540340481, 1.3296480321783273,
                 3.0902271006004103, 3.884084454339014, 8.14674345020642,
                 -0.20633295246061872, 4.8394033978354365, 9.634718769267778},
                {-8.881226743639635, 3.2503557838768655, 1.5743738306693165,
                 3.406673134696579, 3.9015852305624588, 8.131799611848557,
                 -0.34385142399279905, 4.94212149241632, 9.565457097350846},
                {-8.7776623144254, 2.781883751258725, 1.3865908730714442,
                 3.611459588718801, 3.9332709461076028, 7.988392471771565,
                 -0.05672995961880781, 4.826181853948443, 9.764239122585312},
                {-8.816911571091712, 3.1991146888699045, 1.682586956929247,
                 3.6395817257396885, 3.929428788673067, 8.045839184937563,
                 -0.0599596920066747, 4.754872460873274, 9.849888475645084}},
            Eigen::ArrayXXd{
                {7.566874055194999, 0.6871959485158655, 2.5241514837999377,
                 1.036263527533751, 13.042700975420962, 2.026739478883988,
                 1.990905863227943, 1.6580752595784025, 1.8734439668353118},
                {7.565694841620813, 0.7418325513940617, 2.436887017888663,
                 1.2948767299832815, 12.36733476520777, 2.2820427967522505,
                 2.0137732909032118, 1.5521856531793925, 1.8418082671055118},
                {7.4795691474325885, 0.7076966186002148, 2.5340485396884613,
                 1.2224433851093919, 13.306542551860908, 2.2796332053990898,
                 2.033416368489438, 1.4439565720118002, 1.8066718452767003},
                {7.431627649647245, 0.8468724010782427, 2.513432570242262,
                 1.0998837267302095, 13.563256881297269, 2.2072242850531145,
                 1.8796274790186436, 1.5637335998667963, 1.8732883215110505},
                {7.555978293337988, 0.7297589179642044, 2.3848375360290306,
                 1.07950185569713, 13.637625448141778, 2.2467411282149032,
                 1.8836367316490117, 1.6154566696643367, 1.8687148411888548}},
            Eigen::ArrayXXd{
                {0.36738871833107384, 0.9448098790118532, 0.22656215442572927,
                 0.8905100055952561, 0.28071751805915834, 0.21273571287803847,
                 0.071249991156245, 0.05185002595184627, 0.8200553731138187},
                {0.35583847947123265, 0.8547208948720537, 0.05903748203472455,
                 0.1586423819710866, 0.13424381745969668, 0.9157052963827358,
                 0.5301864587829327, 0.4886809726531329, 0.49538595869685054},
                {0.0818189392513522, 0.9132185440763189, 0.6797648279095293,
                 0.5611158470416412, 0.359635919781754, 0.8816195882328763,
                 0.25071188696623103, 0.6428271025073086, 0.36896509343710016},
                {0.8617387778723746, 0.5431097657673061, 0.20012447234371863,
                 0.7997521359689561, 0.790538998105682, 0.5588466131387823,
                 0.8227835690822748, 0.46808169503293484, 0.736469401263631},
                {0.5671954525495728, 0.8763846994841177, 0.9468898219787074,
                 0.830398320712941, 0.7382747350603198, 0.6868447186869612,
                 0.8167063888701163, 0.35462006038818106, 0.8968646093299735}})
    };
  }

  void TearDown() override {}
};

TEST_F(TruncatedGaussianTest, VCDF) {
  for (auto test : tests) {
    auto got =
        stats::multivariates::IndependentTruncatedGaussian(test.mu_, test.std_, test.a_, test.b_)
            .cdf(test.x_);
    auto maxDiff = (got - test.cdf_).abs().maxCoeff();
    EXPECT_THAT(maxDiff, testing::Lt(1e-12));
  }
}
TEST_F(TruncatedGaussianTest, CDF) {
  for (auto test : tests) {
    stats::multivariates::IndependentTruncatedGaussian d(test.mu_, test.std_,
                                                         test.a_, test.b_);
    int n = test.x_.rows();
    for (int i = 0; i < n; i++) {
      Eigen::ArrayXd got = d.cdf(Eigen::ArrayXd(test.x_.row(i)));
      EXPECT_THAT((got - (Eigen::ArrayXd)test.cdf_.row(i)).abs().maxCoeff(),
                  testing::Lt(1e-12));
    }
  }
}
TEST_F(TruncatedGaussianTest, VPDF) {
  for (auto test : tests) {
    auto got =
        stats::multivariates::IndependentTruncatedGaussian(test.mu_, test.std_, test.a_, test.b_)
            .pdf(test.x_);
    auto maxDiff = (got - test.pdf_).abs().maxCoeff();
    EXPECT_THAT(maxDiff, testing::Lt(1e-12));
  }
}
TEST_F(TruncatedGaussianTest, PDF) {
  for (auto test : tests) {
    stats::multivariates::IndependentTruncatedGaussian d(test.mu_, test.std_,
                                                         test.a_, test.b_);
    int n = test.x_.rows();
    for (int i = 0; i < n; i++) {
      Eigen::ArrayXd got = d.pdf(Eigen::ArrayXd(test.x_.row(i)));
      EXPECT_THAT((got - (Eigen::ArrayXd)test.pdf_.row(i)).abs().maxCoeff(),
                  testing::Lt(1e-12));
    }
  }
}

TEST_F(TruncatedGaussianTest, PPF) {
  for (auto test : tests) {
    stats::multivariates::IndependentTruncatedGaussian d(test.mu_, test.std_,
                                                         test.a_, test.b_);
    int n = test.x_.rows();
    for (int i = 0; i < n; i++) {
      Eigen::ArrayXd got = d.ppf(Eigen::ArrayXd(test.cdf_.row(i)));
      EXPECT_THAT((got - (Eigen::ArrayXd)test.x_.row(i)).abs().maxCoeff(),
                  testing::Lt(1e-12));
    }
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
