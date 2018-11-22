#pragma once

#include <map>

#include "simplicity/types/global_events_types.h"

namespace simplicity {

GlobalEventsError RegisterEvent(const Event& event, Callback callback);
GlobalEventsError ProcessEvent(const Event& event);

static std::map <Event, Callback> event_map_;

}  // namespace simplicity
