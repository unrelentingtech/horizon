#pragma once
#include "core/tool.hpp"

namespace horizon {
class ToolHelperMapSymbol : public virtual ToolBase {
public:
    using ToolBase::ToolBase;

    class Settings : public ToolSettings {
    public:
        json serialize() const override;
        void load_from_json(const json &j) override;
        std::map<UUID, UUID> selected_symbols;
    };

    std::map<ToolID, ToolSettings *> get_all_settings() override;

protected:
    class SchematicSymbol *map_symbol(class Component *c, const class Gate *g, const UUID &sym_default = UUID());
    const class Symbol *get_symbol_for_unit(const UUID &unit_uu, bool *auto_selected = nullptr,
                                            const UUID &sym_default = UUID());
    void change_symbol(class SchematicSymbol *schsym);

private:
    Settings settings;
};
} // namespace horizon
