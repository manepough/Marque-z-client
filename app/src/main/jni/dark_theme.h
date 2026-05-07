// ManesClient UI Theme
// Dark steel background + cyan/teal accent
// Distinct from original purple scheme

void embraceTheDarkness()
{
    ImVec4* colors = ImGui::GetStyle().Colors;

    // ── Text ────────────────────────────────────────────────────────────────
    colors[ImGuiCol_Text]                   = ImVec4(0.92f, 0.95f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.38f, 0.42f, 0.50f, 1.00f);

    // ── Windows ─────────────────────────────────────────────────────────────
    colors[ImGuiCol_WindowBg]               = ImVec4(0.04f, 0.06f, 0.10f, 0.92f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.03f, 0.05f, 0.09f, 0.60f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.06f, 0.08f, 0.14f, 0.96f);

    // ── Borders — thin cyan glow ─────────────────────────────────────────────
    colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.75f, 0.85f, 0.65f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);

    // ── Frame ───────────────────────────────────────────────────────────────
    colors[ImGuiCol_FrameBg]                = ImVec4(0.06f, 0.09f, 0.16f, 0.80f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.00f, 0.55f, 0.65f, 0.30f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.00f, 0.65f, 0.75f, 0.45f);

    // ── Title bar ───────────────────────────────────────────────────────────
    colors[ImGuiCol_TitleBg]                = ImVec4(0.02f, 0.04f, 0.08f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.00f, 0.40f, 0.50f, 0.80f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.02f, 0.04f, 0.08f, 0.50f);

    // ── Menu bar ────────────────────────────────────────────────────────────
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.03f, 0.05f, 0.10f, 1.00f);

    // ── Scrollbar ───────────────────────────────────────────────────────────
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.03f, 0.05f, 0.09f, 0.60f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.00f, 0.60f, 0.70f, 0.55f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.00f, 0.70f, 0.82f, 0.70f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.00f, 0.82f, 0.95f, 1.00f);

    // ── Checkmark + sliders — bright cyan ───────────────────────────────────
    colors[ImGuiCol_CheckMark]              = ImVec4(0.00f, 0.88f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.00f, 0.75f, 0.88f, 0.90f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.00f, 0.90f, 1.00f, 1.00f);

    // ── Buttons ─────────────────────────────────────────────────────────────
    colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.08f, 0.15f, 0.80f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.00f, 0.55f, 0.65f, 0.55f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.00f, 0.70f, 0.82f, 0.80f);

    // ── Headers (combo/selectable/tree) ─────────────────────────────────────
    colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.50f, 0.60f, 0.35f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.62f, 0.72f, 0.45f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.00f, 0.72f, 0.84f, 0.60f);

    // ── Separator ───────────────────────────────────────────────────────────
    colors[ImGuiCol_Separator]              = ImVec4(0.00f, 0.55f, 0.65f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.00f, 0.72f, 0.84f, 0.65f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.00f, 0.88f, 1.00f, 0.90f);

    // ── Resize grip ─────────────────────────────────────────────────────────
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.00f, 0.60f, 0.72f, 0.40f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.00f, 0.72f, 0.84f, 0.60f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.00f, 0.88f, 1.00f, 0.95f);

    // ── Tabs ────────────────────────────────────────────────────────────────
    colors[ImGuiCol_Tab]                    = ImVec4(0.03f, 0.06f, 0.12f, 0.90f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.00f, 0.60f, 0.72f, 0.60f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.00f, 0.70f, 0.84f, 0.90f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.03f, 0.06f, 0.12f, 0.60f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.00f, 0.45f, 0.55f, 0.60f);

    // ── Plot ────────────────────────────────────────────────────────────────
    colors[ImGuiCol_PlotLines]              = ImVec4(0.00f, 0.80f, 0.92f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.00f, 0.72f, 0.84f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.00f, 0.90f, 1.00f, 1.00f);

    // ── Tables ──────────────────────────────────────────────────────────────
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.03f, 0.06f, 0.12f, 0.80f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.55f, 0.65f, 0.60f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.00f, 0.40f, 0.48f, 0.35f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.00f, 0.55f, 0.65f, 0.06f);

    // ── Misc ────────────────────────────────────────────────────────────────
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.00f, 0.60f, 0.72f, 0.40f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.00f, 0.88f, 1.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.00f, 0.80f, 0.92f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.00f, 0.75f, 0.88f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.00f, 0.00f, 0.00f, 0.45f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.00f, 0.05f, 0.08f, 0.55f);

    // ── Style / sizing ───────────────────────────────────────────────────────
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding         = ImVec2(10.00f, 10.00f);
    style.FramePadding          = ImVec2(6.00f,  3.00f);
    style.CellPadding           = ImVec2(6.00f,  5.00f);
    style.ItemSpacing           = ImVec2(7.00f,  5.00f);
    style.ItemInnerSpacing      = ImVec2(5.00f,  5.00f);
    style.TouchExtraPadding     = ImVec2(2.00f,  2.00f);
    style.IndentSpacing         = 20;
    style.ScrollbarSize         = 9;
    style.GrabMinSize           = 9;

    // Borders
    style.WindowBorderSize      = 1;
    style.ChildBorderSize       = 1;
    style.PopupBorderSize       = 1;
    style.FrameBorderSize       = 1;
    style.TabBorderSize         = 0;
    style.TabBarBorderSize      = 1;

    // Rounding — softer corners than original
    style.WindowRounding        = 8;
    style.ChildRounding         = 5;
    style.FrameRounding         = 4;
    style.PopupRounding         = 6;
    style.ScrollbarRounding     = 8;
    style.GrabRounding          = 4;
    style.TabRounding            = 5;
    style.LogSliderDeadzone     = 4;
}
