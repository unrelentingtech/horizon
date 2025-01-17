#include "imp_frame.hpp"
#include "canvas/canvas_gl.hpp"
#include "header_button.hpp"
#include "core/tool_id.hpp"
#include "widgets/action_button.hpp"

namespace horizon {
ImpFrame::ImpFrame(const std::string &frame_filename, const std::string &pool_path)
    : ImpBase(pool_path), core_frame(frame_filename, *pool.get()), frame(core_frame.get_frame())
{
    core = &core_frame;
    core_frame.signal_tool_changed().connect(sigc::mem_fun(*this, &ImpBase::handle_tool_change));
}

void ImpFrame::canvas_update()
{
    canvas->update(core_frame.get_canvas_data());
}

void ImpFrame::construct()
{

    state_store = std::make_unique<WindowStateStore>(main_window, "imp-frame");

    header_button = Gtk::manage(new HeaderButton);
    main_window->header->set_custom_title(*header_button);
    header_button->show();
    header_button->signal_closed().connect(sigc::mem_fun(*this, &ImpFrame::update_header));

    name_entry = header_button->add_entry("Name");
    name_entry->set_text(frame.name);
    name_entry->set_width_chars(std::min<int>(frame.name.size(), 20));
    name_entry->signal_changed().connect([this] { core_frame.set_needs_save(); });
    name_entry->signal_activate().connect(sigc::mem_fun(*this, &ImpFrame::update_header));

    core->signal_save().connect([this] { frame.name = name_entry->get_text(); });

    hamburger_menu->append("Frame properties…", "win.edit_frame");
    add_tool_action(ToolID::EDIT_FRAME_PROPERTIES, "edit_frame");

    add_action_button_line();
    add_action_button_polygon();
    add_action_button(ToolID::PLACE_TEXT);


    update_header();
}

void ImpFrame::update_header()
{
    header_button->set_label(name_entry->get_text());
    set_window_title(name_entry->get_text());
}

} // namespace horizon
