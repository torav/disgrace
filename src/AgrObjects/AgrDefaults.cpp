/*
 * AgrDefaults.cpp
 *
 *  Created on: 26 ott 2016
 *      Author: lorenzo
 */

#include "AgrDefaults.h"

#include <QDateTime>

namespace dg {

AgrSettings AgrDefaults::_dataset;
AgrSettings AgrDefaults::_graph;
AgrSettings AgrDefaults::_file;
SettingsMap AgrDefaults::_settings_map;

void AgrDefaults::init_defaults() {
	QStringList to_be_quoted;
	to_be_quoted << "default sformat"
			<< "timestamp def";
	_file.set_paths_to_be_quoted(to_be_quoted);
	QStringList overlapping_keys("timestamp");
	_file.set_overlapping_keys(overlapping_keys);
	_file.put("version", DISGRACE_VERSION);
	_file.put("page size", "800, 517");
	_file.put("page scroll", "5%");
	_file.put("page inout", "5%");
	_file.put("link page", "off");
	_file.put("reference date", "0");
	_file.put("date wrap", "off");
	_file.put("date wrap year", "1950");
	_file.put("default linewidth", "2.5");
	_file.put("default linestyle", "1");
	_file.put("default color", "1");
	_file.put("default pattern", "1");
	_file.put("default font", "0");
	_file.put("default char size", "1.000000");
	_file.put("default symbol size", "1.000000");
	_file.put("default sformat", "\"%.8g\"");
	_file.put("background color", "0");
	_file.put("page background fill", "on");
	_file.put("timestamp", "off");
	_file.put("timestamp", "0.03, 0.03");
	_file.put("timestamp color", "1");
	_file.put("timestamp rot", "0");
	_file.put("timestamp font", "0");
	_file.put("timestamp char size", "1.000000");
	_file.put("timestamp def", QDateTime::currentDateTime().toString("ddd MMM d hh:mm:ss yy"));

	_settings_map.add_line("map color 0 to (255, 255, 255), \"white\"");
	_settings_map.add_line("map color 1 to (0, 0, 0), \"black\"");
	_settings_map.add_line("map color 2 to (255, 0, 0), \"red\"");
	_settings_map.add_line("map color 3 to (0, 255, 0), \"green\"");
	_settings_map.add_line("map color 4 to (0, 0, 255), \"blue\"");
	_settings_map.add_line("map color 5 to (255, 165, 0), \"orange\"");
	_settings_map.add_line("map color 6 to (188, 143, 143), \"brown\"");
	_settings_map.add_line("map color 7 to (200, 200, 200), \"grey\"");
	_settings_map.add_line("map color 8 to (148, 0, 211), \"violet\"");
	_settings_map.add_line("map color 9 to (0, 255, 255), \"cyan\"");
	_settings_map.add_line("map color 10 to (255, 0, 255), \"magenta\"");
	_settings_map.add_line("map color 11 to (139, 0, 0), \"red4\"");
	_settings_map.add_line("map color 12 to (114, 33, 188), \"indigo\"");
	_settings_map.add_line("map color 13 to (103, 7, 72), \"maroon\"");
	_settings_map.add_line("map color 14 to (64, 224, 208), \"turquoise\"");
	_settings_map.add_line("map color 15 to (0, 139, 0), \"green4\"");

	_settings_map.add_line("map font 0 to \"Times-Roman\", \"Times-Roman\"");
	_settings_map.add_line("map font 1 to \"Times-Italic\", \"Times-Italic\"");
	_settings_map.add_line("map font 2 to \"Times-Bold\", \"Times-Bold\"");
	_settings_map.add_line("map font 3 to \"Times-BoldItalic\", \"Times-BoldItalic\"");
	_settings_map.add_line("map font 4 to \"Helvetica\", \"Helvetica\"");
	_settings_map.add_line("map font 5 to \"Helvetica-Oblique\", \"Helvetica-Oblique\"");
	_settings_map.add_line("map font 6 to \"Helvetica-Bold\", \"Helvetica-Bold\"");
	_settings_map.add_line("map font 7 to \"Helvetica-BoldOblique\", \"Helvetica-BoldOblique\"");
	_settings_map.add_line("map font 8 to \"Courier\", \"Courier\"");
	_settings_map.add_line("map font 9 to \"Courier-Oblique\", \"Courier-Oblique\"");
	_settings_map.add_line("map font 10 to \"Courier-Bold\", \"Courier-Bold\"");
	_settings_map.add_line("map font 11 to \"Courier-BoldOblique\", \"Courier-BoldOblique\"");
	_settings_map.add_line("map font 12 to \"Symbol\", \"Symbol\"");
	_settings_map.add_line("map font 13 to \"ZapfDingbats\", \"ZapfDingbats\"");
	_settings_map.add_line("map font 14 to \"Courier-Regular\", \"Courier-Regular\"");
	_settings_map.add_line("map font 15 to \"Dingbats-Regular\", \"Dingbats-Regular\"");
	_settings_map.add_line("map font 20 to \"NimbusMonoL-Bold\", \"NimbusMonoL-Bold\"");
	_settings_map.add_line("map font 21 to \"NimbusMonoL-BoldOblique\", \"NimbusMonoL-BoldOblique\"");
	_settings_map.add_line("map font 22 to \"NimbusMonoL-Regular\", \"NimbusMonoL-Regular\"");
	_settings_map.add_line("map font 23 to \"NimbusMonoL-RegularOblique\", \"NimbusMonoL-RegularOblique\"");
	_settings_map.add_line("map font 24 to \"NimbusRomanNo9L-Medium\", \"NimbusRomanNo9L-Medium\"");
	_settings_map.add_line("map font 25 to \"NimbusRomanNo9L-MediumItalic\", \"NimbusRomanNo9L-MediumItalic\"");
	_settings_map.add_line("map font 26 to \"NimbusRomanNo9L-Regular\", \"NimbusRomanNo9L-Regular\"");
	_settings_map.add_line("map font 27 to \"NimbusRomanNo9L-RegularItalic\", \"NimbusRomanNo9L-RegularItalic\"");
	_settings_map.add_line("map font 28 to \"NimbusSansL-Bold\", \"NimbusSansL-Bold\"");
	_settings_map.add_line("map font 29 to \"NimbusSansL-BoldCondensed\", \"NimbusSansL-BoldCondensed\"");
	_settings_map.add_line("map font 30 to \"NimbusSansL-BoldCondensedItalic\", \"NimbusSansL-BoldCondensedItalic\"");
	_settings_map.add_line("map font 31 to \"NimbusSansL-BoldItalic\", \"NimbusSansL-BoldItalic\"");
	_settings_map.add_line("map font 32 to \"NimbusSansL-Regular\", \"NimbusSansL-Regular\"");
	_settings_map.add_line("map font 33 to \"NimbusSansL-RegularCondensed\", \"NimbusSansL-RegularCondensed\"");
	_settings_map.add_line("map font 34 to \"NimbusSansL-RegularCondensedItalic\", \"NimbusSansL-RegularCondensedItalic\"");
	_settings_map.add_line("map font 35 to \"NimbusSansL-RegularItalic\", \"NimbusSansL-RegularItalic\"");
	_settings_map.add_line("map font 36 to \"StandardSymbolsL-Regular\", \"StandardSymbolsL-Regular\"");
	_settings_map.add_line("map font 38 to \"Symbol-Regular\", \"Symbol-Regular\"");
	_settings_map.add_line("map font 43 to \"URWBookmanL-DemiBold\", \"URWBookmanL-DemiBold\"");
	_settings_map.add_line("map font 44 to \"URWBookmanL-DemiBoldItalic\", \"URWBookmanL-DemiBoldItalic\"");
	_settings_map.add_line("map font 45 to \"URWBookmanL-Light\", \"URWBookmanL-Light\"");
	_settings_map.add_line("map font 46 to \"URWBookmanL-LightItalic\", \"URWBookmanL-LightItalic\"");
	_settings_map.add_line("map font 47 to \"URWChanceryL-MediumItalic\", \"URWChanceryL-MediumItalic\"");
	_settings_map.add_line("map font 48 to \"URWGothicL-Book\", \"URWGothicL-Book\"");
	_settings_map.add_line("map font 49 to \"URWGothicL-BookOblique\", \"URWGothicL-BookOblique\"");
	_settings_map.add_line("map font 50 to \"URWGothicL-Demi\", \"URWGothicL-Demi\"");
	_settings_map.add_line("map font 51 to \"URWGothicL-DemiOblique\", \"URWGothicL-DemiOblique\"");
	_settings_map.add_line("map font 52 to \"URWPalladioL-Bold\", \"URWPalladioL-Bold\"");
	_settings_map.add_line("map font 53 to \"URWPalladioL-BoldItalic\", \"URWPalladioL-BoldItalic\"");
	_settings_map.add_line("map font 54 to \"URWPalladioL-Italic\", \"URWPalladioL-Italic\"");
	_settings_map.add_line("map font 55 to \"URWPalladioL-Roman\", \"URWPalladioL-Roman\"");
	_settings_map.add_line("map font 56 to \"Utopia-Bold\", \"Utopia-Bold\"");
	_settings_map.add_line("map font 57 to \"Utopia-BoldItalic\", \"Utopia-BoldItalic\"");
	_settings_map.add_line("map font 58 to \"Utopia-Italic\", \"Utopia-Italic\"");
	_settings_map.add_line("map font 59 to \"Utopia-Regular\", \"Utopia-Regular\"");

	to_be_quoted.clear();
	to_be_quoted << "title"
			<< "subtitle"
			<< "xaxis label"
			<< "xaxis ticklabel formula"
			<< "xaxis ticklabel append"
			<< "xaxis ticklabel prepend"
			<< "yaxis label"
			<< "yaxis ticklabel formula"
			<< "yaxis ticklabel append"
			<< "yaxis ticklabel prepend"
			<< "altxaxis ticklabel formula"
			<< "altxaxis ticklabel append"
			<< "altxaxis ticklabel prepend"
			<< "altyaxis ticklabel formula"
			<< "altyaxis ticklabel append"
			<< "altyaxis ticklabel prepend";
	_graph.set_paths_to_be_quoted(to_be_quoted);
	overlapping_keys.clear();
	overlapping_keys << "legend";
	_graph.set_overlapping_keys(overlapping_keys);
	_graph.put("hidden", "false");
	_graph.put("type", "XY");
	_graph.put("stacked", "false");
	_graph.put("bar hgap", "0.000000");
	_graph.put("fixedpoint", "off");
	_graph.put("fixedpoint type", "0");
	_graph.put("fixedpoint xy", "0.000000, 0.000000");
	_graph.put("fixedpoint format general", "general");
	_graph.put("fixedpoint prec", "6, 6");
	_graph.put("world", "0, 0, 1, 1");
	_graph.put("stack world", "0, 0, 0, 0");
	_graph.put("znorm", "1");
	_graph.put("view", "0.150000, 0.150000, 1.495746, 0.950000");
	_graph.put("title", "\"\"");
	_graph.put("title font", "0");
	_graph.put("title size", "2.250000");
	_graph.put("title color", "1");
	_graph.put("subtitle", "\"\"");
	_graph.put("subtitle font", "0");
	_graph.put("subtitle size", "1.750000");
	_graph.put("subtitle color", "1");
	_graph.put("xaxes scale", "Normal");
	_graph.put("yaxes scale", "Normal");
	_graph.put("xaxes invert", "off");
	_graph.put("yaxes invert", "off");
	_graph.put("xaxis", "on");
	_graph.put("xaxis type zero", "false");
	_graph.put("xaxis offset", "0.000000 , 0.000000");
	_graph.put("xaxis bar", "on");
	_graph.put("xaxis bar color", "1");
	_graph.put("xaxis bar linestyle", "1");
	_graph.put("xaxis bar linewidth", "2.5");
	_graph.put("xaxis label", "\"\"");
	_graph.put("xaxis label layout", "para");
	_graph.put("xaxis label place", "auto");
	_graph.put("xaxis label char size", "2.250000");
	_graph.put("xaxis label font", "0");
	_graph.put("xaxis label color", "1");
	_graph.put("xaxis label place", "normal");
	_graph.put("xaxis tick", "on");
	_graph.put("xaxis tick major", "0.2");
	_graph.put("xaxis tick minor ticks", "1");
	_graph.put("xaxis tick default", "6");
	_graph.put("xaxis tick place rounded", "true");
	_graph.put("xaxis tick", "in");
	_graph.put("xaxis tick major size", "1.500000");
	_graph.put("xaxis tick major color", "1");
	_graph.put("xaxis tick major linewidth", "2.5");
	_graph.put("xaxis tick major linestyle", "1");
	_graph.put("xaxis tick major grid", "off");
	_graph.put("xaxis tick minor color", "1");
	_graph.put("xaxis tick minor linewidth", "1.5");
	_graph.put("xaxis tick minor linestyle", "1");
	_graph.put("xaxis tick minor grid", "off");
	_graph.put("xaxis tick minor size", "0.750000");
	_graph.put("xaxis ticklabel", "on");
	_graph.put("xaxis ticklabel format", "general");
	_graph.put("xaxis ticklabel prec", "5");
	_graph.put("xaxis ticklabel formula", "\"\"");
	_graph.put("xaxis ticklabel append", "\"\"");
	_graph.put("xaxis ticklabel prepend", "\"\"");
	_graph.put("xaxis ticklabel angle", "0");
	_graph.put("xaxis ticklabel skip", "0");
	_graph.put("xaxis ticklabel stagger", "0");
	_graph.put("xaxis ticklabel place", "normal");
	_graph.put("xaxis ticklabel offset", "auto");
	_graph.put("xaxis ticklabel offset", "0.000000 , 0.010000");
	_graph.put("xaxis ticklabel start type", "auto");
	_graph.put("xaxis ticklabel start", "0.000000");
	_graph.put("xaxis ticklabel stop type", "auto");
	_graph.put("xaxis ticklabel stop", "0.000000");
	_graph.put("xaxis ticklabel char size", "1.750000");
	_graph.put("xaxis ticklabel font", "0");
	_graph.put("xaxis ticklabel color", "1");
	_graph.put("xaxis tick place", "both");
	_graph.put("xaxis tick spec type", "none");
	_graph.put("yaxis", "on");
	_graph.put("yaxis type zero", "false");
	_graph.put("yaxis offset", "0.000000 , 0.000000");
	_graph.put("yaxis bar", "on");
	_graph.put("yaxis bar", "color 1");
	_graph.put("yaxis bar", "linestyle 1");
	_graph.put("yaxis bar", "linewidth 2.5");
	_graph.put("yaxis label", "\"\"");
	_graph.put("yaxis label layout", "para");
	_graph.put("yaxis label place", "auto");
	_graph.put("yaxis label char size", "2.250000");
	_graph.put("yaxis label font", "0");
	_graph.put("yaxis label color", "1");
	_graph.put("yaxis label place", "normal");
	_graph.put("yaxis tick", "on");
	_graph.put("yaxis tick major", "0.2");
	_graph.put("yaxis tick minor ticks", "1");
	_graph.put("yaxis tick default", "6");
	_graph.put("yaxis tick place rounded", "true");
	_graph.put("yaxis tick", "in");
	_graph.put("yaxis tick major size", "1.500000");
	_graph.put("yaxis tick major color", "1");
	_graph.put("yaxis tick major linewidth", "2.5");
	_graph.put("yaxis tick major linestyle", "1");
	_graph.put("yaxis tick major grid", "off");
	_graph.put("yaxis tick minor color", "1");
	_graph.put("yaxis tick minor linewidth", "1.5");
	_graph.put("yaxis tick minor linestyle", "1");
	_graph.put("yaxis tick minor grid", "off");
	_graph.put("yaxis tick minor size", "0.750000");
	_graph.put("yaxis ticklabel", "on");
	_graph.put("yaxis ticklabel format", "general");
	_graph.put("yaxis ticklabel prec", "5");
	_graph.put("yaxis ticklabel formula", "\"\"");
	_graph.put("yaxis ticklabel append", "\"\"");
	_graph.put("yaxis ticklabel prepend", "\"\"");
	_graph.put("yaxis ticklabel angle", "0");
	_graph.put("yaxis ticklabel skip", "0");
	_graph.put("yaxis ticklabel stagger", "0");
	_graph.put("yaxis ticklabel place", "normal");
	_graph.put("yaxis ticklabel offset", "auto");
	_graph.put("yaxis ticklabel offset", "0.000000 , 0.010000");
	_graph.put("yaxis ticklabel start type", "auto");
	_graph.put("yaxis ticklabel start", "0.000000");
	_graph.put("yaxis ticklabel stop type", "auto");
	_graph.put("yaxis ticklabel stop", "0.000000");
	_graph.put("yaxis ticklabel char size", "1.750000");
	_graph.put("yaxis ticklabel font", "0");
	_graph.put("yaxis ticklabel color", "1");
	_graph.put("yaxis tick place", "both");
	_graph.put("yaxis tick spec type", "none");
	_graph.put("altxaxis", "off");
	_graph.put("altyaxis", "off");
	_graph.put("legend", "on");
	_graph.put("legend loctype", "view");
	_graph.put("legend", "0.85, 0.8");
	_graph.put("legend box color", "1");
	_graph.put("legend box pattern", "1");
	_graph.put("legend box linewidth", "1.0");
	_graph.put("legend box linestyle", "0");
	_graph.put("legend box fill color", "0");
	_graph.put("legend box fill pattern", "1");
	_graph.put("legend font", "0");
	_graph.put("legend char size", "1.750000");
	_graph.put("legend color", "1");
	_graph.put("legend length", "5");
	_graph.put("legend vgap", "1");
	_graph.put("legend hgap", "1");
	_graph.put("legend invert", "false");
	_graph.put("frame type", "0");
	_graph.put("frame linestyle", "1");
	_graph.put("frame linewidth", "1.0");
	_graph.put("frame color", "1");
	_graph.put("frame pattern", "1");
	_graph.put("frame background color", "0");
	_graph.put("frame background pattern", "0");

	to_be_quoted.clear();
	to_be_quoted << "legend"
			<< "comment"
			<< "avalue prepend"
			<< "avalue append";
	_dataset.set_paths_to_be_quoted(to_be_quoted);
	// TODO: update these defaults with the ones stored in the _file settings tree
	_dataset.put("hidden", "false");
	_dataset.put("type", "xy");
	_dataset.put("symbol", "0");
	_dataset.put("symbol size", "1.000000");
	_dataset.put("symbol color", "1");
	_dataset.put("symbol pattern", "1");
	_dataset.put("symbol fill color", "1");
	_dataset.put("symbol fill pattern", "0");
	_dataset.put("symbol linewidth", "1.0");
	_dataset.put("symbol linestyle", " 1");
	_dataset.put("symbol char", "65");
	_dataset.put("symbol char font", "0");
	_dataset.put("symbol skip", "0");
	_dataset.put("line type", "1");
	_dataset.put("line linestyle", "1");
	_dataset.put("line linewidth", "2.0");
	_dataset.put("line color", "1");
	_dataset.put("line pattern", "1");
	_dataset.put("baseline ", "0");
	_dataset.put("baseline", "off");
	_dataset.put("dropline", "off");
	_dataset.put("fill type", "0");
	_dataset.put("fill rule ", "");
	_dataset.put("fill color", "1");
	_dataset.put("fill pattern", "1");
	_dataset.put("avalue", "off");
	_dataset.put("avalue type", "2");
	_dataset.put("avalue char size", "1.000000");
	_dataset.put("avalue font", "0");
	_dataset.put("avalue color", "1");
	_dataset.put("avalue rot", "0");
	_dataset.put("avalue format", "general");
	_dataset.put("avalue prec", "3");
	_dataset.put("avalue prepend", "\"\"");
	_dataset.put("avalue append", "\"\"");
	_dataset.put("avalue offset", "0.000000 , 0.000000");
	_dataset.put("errorbar", "on");
	_dataset.put("errorbar place", "both");
	_dataset.put("errorbar color", "1");
	_dataset.put("errorbar pattern", "1");
	_dataset.put("errorbar size", "1.000000");
	_dataset.put("errorbar linewidth", "1.0");
	_dataset.put("errorbar linestyle", "1");
	_dataset.put("errorbar riser linewidth", "1.0");
	_dataset.put("errorbar riser linestyle", "1");
	_dataset.put("errorbar riser clip ", "off");
	_dataset.put("errorbar riser clip length", "0.100000");
	_dataset.put("comment", "");
	_dataset.put("legend", "");
}

AgrDefaults::AgrDefaults() {

}

AgrDefaults::~AgrDefaults() {

}

} /* namespace dg */
