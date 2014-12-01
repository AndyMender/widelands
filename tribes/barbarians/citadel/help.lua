-- The Barbarian Citadel

include "data/scripting/formatting.lua"
include "tribes/scripting/format_help.lua"

set_textdomain("tribe_barbarians")

return {
   func = function(building_description)
	return

	--Lore Section
	building_help_lore_string("barbarians", building_description, _[[Text needed]], _[[Source needed]]) ..
	--General Section
	building_help_general_string("barbarians", building_description,
		_"Garrisons soldiers to expand your territory.",
		_"If you’re low on soldiers to occupy new military sites, use the downward arrow button to decrease the capacity. You can also click on a soldier to send him away.") ..

	--Building Section
	building_help_building_section("barbarians", building_description, "fortress", {"fortress"})
   end
}
