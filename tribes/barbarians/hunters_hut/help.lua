-- The Barbarian Hunter's Hut

include "data/scripting/formatting.lua"
include "tribes/scripting/format_help.lua"

set_textdomain("tribe_barbarians")

return {
   func = function(building_description)
	return

	--Lore Section
	building_help_lore_string("barbarians", building_description, _[[‘As silent as a panther,<br> as deft as a weasel,<br> as swift as an arrow,<br> as deadly as a viper.’]], _[[‘The Art of Hunting’]]) ..

	--General Section
	building_help_general_string("barbarians", building_description,
		_"Hunts animals to produce meat.",
		_"The hunter’s hut needs animals to hunt within the working radius.") ..

	--Dependencies
	building_help_dependencies_production("barbarians", building_description) ..

	--Workers Section
	building_help_crew_string("barbarians", building_description) ..

	--Building Section
	building_help_building_section("barbarians", building_description) ..

	--Production Section
	building_help_production_section(_"The hunter pauses %s before going to work again.":bformat(
		ngettext("%d second", "%d seconds", 35):bformat(35)
	))
   end
}
