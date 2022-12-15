//------------------------------------------------------------------------------
// LICENSE
//   This software is dual-licensed to the public domain and under the following
//   license: you are granted a perpetual, irrevocable license to copy, modify,
//   publish, and distribute this file as you see fit.
//
// CREDITS
//   Written by Michal Cichon
//------------------------------------------------------------------------------
#ifndef __IMGUI_NODE_EDITOR_H__
#define __IMGUI_NODE_EDITOR_H__
#pragma once

//------------------------------------------------------------------------------
#include <cstdint> // std::uintXX_t
#include <imgui.h>
#include <utility> // std::move
#include <vector>

#define IMGUI_DEFINE_MATH_OPERATORS

//------------------------------------------------------------------------------
namespace ax {
namespace NodeEditor {

//------------------------------------------------------------------------------
struct NodeId;
struct LinkId;
struct PinId;

//------------------------------------------------------------------------------
enum class SaveReasonFlags : uint32_t {
    None = 0x00000000,
    Navigation = 0x00000001,
    Position = 0x00000002,
    Size = 0x00000004,
    Selection = 0x00000008,
    User = 0x00000010
};

inline SaveReasonFlags operator|(SaveReasonFlags lhs, SaveReasonFlags rhs)
{
    return static_cast<SaveReasonFlags>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}
inline SaveReasonFlags operator&(SaveReasonFlags lhs, SaveReasonFlags rhs)
{
    return static_cast<SaveReasonFlags>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

using ConfigSaveSettings = bool (*)(const char* data, size_t size, SaveReasonFlags reason, void* userPointer);
using ConfigLoadSettings = size_t (*)(char* data, void* userPointer);

using ConfigSaveNodeSettings = bool (*)(NodeId nodeId, const char* data, size_t size, SaveReasonFlags reason, void* userPointer);
using ConfigLoadNodeSettings = size_t (*)(NodeId nodeId, char* data, void* userPointer);

using ConfigSession = void (*)(void* userPointer);

struct Config {
    const char* SettingsFile;
    ConfigSession BeginSaveSession;
    ConfigSession EndSaveSession;
    ConfigSaveSettings SaveSettings;
    ConfigLoadSettings LoadSettings;
    ConfigSaveNodeSettings SaveNodeSettings;
    ConfigLoadNodeSettings LoadNodeSettings;
    void* UserPointer;

    Config()
        : SettingsFile("NodeEditor.json")
        , BeginSaveSession(nullptr)
        , EndSaveSession(nullptr)
        , SaveSettings(nullptr)
        , LoadSettings(nullptr)
        , SaveNodeSettings(nullptr)
        , LoadNodeSettings(nullptr)
        , UserPointer(nullptr)
    {
    }
};

//------------------------------------------------------------------------------
enum class PinKind {
    Input,
    Output
};

//------------------------------------------------------------------------------
enum StyleColor {
    StyleColor_Bg,
    StyleColor_Grid,
    StyleColor_NodeBg,
    StyleColor_NodeBorder,
    StyleColor_HovNodeBorder,
    StyleColor_SelNodeBorder,
    StyleColor_NodeSelRect,
    StyleColor_NodeSelRectBorder,
    StyleColor_HovLinkBorder,
    StyleColor_SelLinkBorder,
    StyleColor_LinkSelRect,
    StyleColor_LinkSelRectBorder,
    StyleColor_PinRect,
    StyleColor_PinRectBorder,
    StyleColor_Flow,
    StyleColor_FlowMarker,
    StyleColor_GroupBg,
    StyleColor_GroupBorder,

    StyleColor_Count
};

enum StyleVar {
    StyleVar_NodePadding,
    StyleVar_NodeRounding,
    StyleVar_NodeBorderWidth,
    StyleVar_HoveredNodeBorderWidth,
    StyleVar_SelectedNodeBorderWidth,
    StyleVar_PinRounding,
    StyleVar_PinBorderWidth,
    StyleVar_LinkStrength,
    StyleVar_SourceDirection,
    StyleVar_TargetDirection,
    StyleVar_ScrollDuration,
    StyleVar_FlowMarkerDistance,
    StyleVar_FlowSpeed,
    StyleVar_FlowDuration,
    StyleVar_PivotAlignment,
    StyleVar_PivotSize,
    StyleVar_PivotScale,
    StyleVar_PinCorners,
    StyleVar_PinRadius,
    StyleVar_PinArrowSize,
    StyleVar_PinArrowWidth,
    StyleVar_GroupRounding,
    StyleVar_GroupBorderWidth,

    StyleVar_Count
};

struct Style {
    ImVec4 NodePadding;
    float NodeRounding;
    float NodeBorderWidth;
    float HoveredNodeBorderWidth;
    float SelectedNodeBorderWidth;
    float PinRounding;
    float PinBorderWidth;
    float LinkStrength;
    ImVec2 SourceDirection;
    ImVec2 TargetDirection;
    float ScrollDuration;
    float FlowMarkerDistance;
    float FlowSpeed;
    float FlowDuration;
    ImVec2 PivotAlignment;
    ImVec2 PivotSize;
    ImVec2 PivotScale;
    float PinCorners;
    float PinRadius;
    float PinArrowSize;
    float PinArrowWidth;
    float GroupRounding;
    float GroupBorderWidth;
    ImVec4 Colors[StyleColor_Count];

    Style()
    {
        NodePadding = ImVec4(8, 8, 8, 8);
        NodeRounding = 12.0f;
        NodeBorderWidth = 1.5f;
        HoveredNodeBorderWidth = 3.5f;
        SelectedNodeBorderWidth = 3.5f;
        PinRounding = 4.0f;
        PinBorderWidth = 0.0f;
        LinkStrength = 100.0f;
        SourceDirection = ImVec2(1.0f, 0.0f);
        TargetDirection = ImVec2(-1.0f, 0.0f);
        ScrollDuration = 0.35f;
        FlowMarkerDistance = 30.0f;
        FlowSpeed = 150.0f;
        FlowDuration = 2.0f;
        PivotAlignment = ImVec2(0.5f, 0.5f);
        PivotSize = ImVec2(0.0f, 0.0f);
        PivotScale = ImVec2(1, 1);
        PinCorners = ImDrawFlags_RoundCornersAll;
        PinRadius = 0.0f;
        PinArrowSize = 0.0f;
        PinArrowWidth = 0.0f;
        GroupRounding = 6.0f;
        GroupBorderWidth = 1.0f;

        Colors[StyleColor_Bg] = ImVec4(60, 60, 70, 200);
        Colors[StyleColor_Grid] = ImVec4(120, 120, 120, 40);
        Colors[StyleColor_NodeBg] = ImVec4(32, 32, 32, 200);
        Colors[StyleColor_NodeBorder] = ImVec4(255, 255, 255, 96);
        Colors[StyleColor_HovNodeBorder] = ImVec4(50, 176, 255, 255);
        Colors[StyleColor_SelNodeBorder] = ImVec4(255, 176, 50, 255);
        Colors[StyleColor_NodeSelRect] = ImVec4(5, 130, 255, 64);
        Colors[StyleColor_NodeSelRectBorder] = ImVec4(5, 130, 255, 128);
        Colors[StyleColor_HovLinkBorder] = ImVec4(50, 176, 255, 255);
        Colors[StyleColor_SelLinkBorder] = ImVec4(255, 176, 50, 255);
        Colors[StyleColor_LinkSelRect] = ImVec4(5, 130, 255, 64);
        Colors[StyleColor_LinkSelRectBorder] = ImVec4(5, 130, 255, 128);
        Colors[StyleColor_PinRect] = ImVec4(60, 180, 255, 100);
        Colors[StyleColor_PinRectBorder] = ImVec4(60, 180, 255, 128);
        Colors[StyleColor_Flow] = ImVec4(255, 128, 64, 255);
        Colors[StyleColor_FlowMarker] = ImVec4(255, 128, 64, 255);
        Colors[StyleColor_GroupBg] = ImVec4(0, 0, 0, 160);
        Colors[StyleColor_GroupBorder] = ImVec4(255, 255, 255, 32);
    }
};

//------------------------------------------------------------------------------
struct EditorContext;

//------------------------------------------------------------------------------
void SetCurrentEditor(EditorContext* ctx);
EditorContext* GetCurrentEditor();
EditorContext* CreateEditor(const Config* config = nullptr);
void DestroyEditor(EditorContext* ctx);

Style& GetStyle();
const char* GetStyleColorName(StyleColor colorIndex);

void PushStyleColor(StyleColor colorIndex, const ImVec4& color);
void PopStyleColor(int count = 1);

void PushStyleVar(StyleVar varIndex, float value);
void PushStyleVar(StyleVar varIndex, const ImVec2& value);
void PushStyleVar(StyleVar varIndex, const ImVec4& value);
void PopStyleVar(int count = 1);

void Begin(const char* id, const ImVec2& size = ImVec2(0, 0));
void End();

void BeginNode(NodeId id);
void BeginPin(PinId id, PinKind kind);
void PinRect(const ImVec2& a, const ImVec2& b);
void PinPivotRect(const ImVec2& a, const ImVec2& b);
void PinPivotSize(const ImVec2& size);
void PinPivotScale(const ImVec2& scale);
void PinPivotAlignment(const ImVec2& alignment);
void EndPin();
void Group(const ImVec2& size);
void EndNode();

bool BeginGroupHint(NodeId nodeId);
ImVec2 GetGroupMin();
ImVec2 GetGroupMax();
void GetGroupContainedIds(NodeId id, std::vector<NodeId>* ids);
ImDrawList* GetHintForegroundDrawList();
ImDrawList* GetHintBackgroundDrawList();
void EndGroupHint();

// TODO: Add a way to manage node background channels
ImDrawList* GetNodeBackgroundDrawList(NodeId nodeId);

bool Link(LinkId id, PinId startPinId, PinId endPinId, const ImVec4& color = ImVec4(255, 255, 255, 255), float thickness = 1.0f, bool sameNode = false);
bool LinkDuplicates(const std::vector<std::pair<uint64_t, ImVec4>>& ids, PinId startPinId, PinId endPinId, const ImVec4& color, float thickness, bool sameNode);

void Flow(LinkId linkId, const ImVec4& color = ImVec4(255, 128, 64, 255));

bool BeginCreate(const ImVec4& color = ImVec4(255, 255, 255, 255), float thickness = 1.0f);
bool QueryNewLink(PinId* startId, PinId* endId);
bool QueryNewLink(PinId* startId, PinId* endId, const ImVec4& color, float thickness = 1.0f);
bool QueryNewNode(PinId* pinId);
bool QueryNewNode(PinId* pinId, const ImVec4& color, float thickness = 1.0f);
bool AcceptNewItem();
bool AcceptNewItem(const ImVec4& color, float thickness = 1.0f);
void RejectNewItem();
void RejectNewItem(const ImVec4& color, float thickness = 1.0f);
void EndCreate();

bool BeginDelete();
bool QueryDeletedLink(LinkId* linkId, PinId* startId = nullptr, PinId* endId = nullptr);
bool QueryDeletedNode(NodeId* nodeId);
bool AcceptDeletedItem();
void RejectDeletedItem();
void EndDelete();

void SetNodePosition(NodeId nodeId, const ImVec2& editorPosition);
ImVec2 GetNodePosition(NodeId nodeId);
ImVec2 GetNodeSize(NodeId nodeId);
void CenterNodeOnScreen(NodeId nodeId);

void RestoreNodeState(NodeId nodeId);

void Suspend();
void Resume();
bool IsSuspended();

bool IsActive();

bool HasSelectionChanged();
int GetSelectedObjectCount();
int GetSelectedNodesCount();
int GetSelectedLinksCount();
int GetSelectedNodes(NodeId* nodes, int size);
int GetSelectedLinks(LinkId* links, int size);
void ClearSelection();
void SelectNode(NodeId nodeId, bool append = false);
void SelectLink(LinkId linkId, bool append = false);
void DeselectNode(NodeId nodeId);
void DeselectLink(LinkId linkId);

bool DeleteNode(NodeId nodeId);
bool DeleteLink(LinkId linkId);

void NavigateToContent(float duration = -1);
void NavigateToSelection(bool zoomIn = false, float duration = -1);

bool ShowNodeContextMenu(NodeId* nodeId);
bool ShowPinContextMenu(PinId* pinId);
bool ShowLinkContextMenu(LinkId* linkId);
bool ShowBackgroundContextMenu();

void EnableShortcuts(bool enable);
bool AreShortcutsEnabled();

bool BeginShortcut();
bool AcceptCut();
bool AcceptCopy();
bool AcceptPaste();
bool AcceptDuplicate();
bool AcceptCreateNode();
int GetActionContextSize();
int GetActionContextNodes(NodeId* nodes, int size);
int GetActionContextLinks(LinkId* links, int size);
void EndShortcut();

float GetCurrentZoom();

NodeId GetDoubleClickedNode();
PinId GetDoubleClickedPin();
LinkId GetDoubleClickedLink();
bool IsBackgroundClicked();
bool IsBackgroundDoubleClicked();

bool PinHadAnyLinks(PinId pinId);

ImVec2 GetScreenSize();
ImVec2 ScreenToCanvas(const ImVec2& pos);
ImVec2 CanvasToScreen(const ImVec2& pos);

//------------------------------------------------------------------------------
namespace Details {

template <typename T, typename Tag>
struct SafeType {
    SafeType(T t)
        : m_Value(std::move(t))
    {
    }

    SafeType(const SafeType&) = default;

    template <typename T2, typename Tag2>
    SafeType(
        const SafeType<
            typename std::enable_if<!std::is_same<T, T2>::value, T2>::type,
            typename std::enable_if<!std::is_same<Tag, Tag2>::value, Tag2>::type>&) = delete;

    SafeType& operator=(const SafeType&) = default;

    explicit operator T() const { return Get(); }

    T Get() const { return m_Value; }

private:
    T m_Value;
};

template <typename Tag>
struct SafePointerType
    : SafeType<uintptr_t, Tag> {
    static const Tag Invalid;

    using SafeType<uintptr_t, Tag>::SafeType;

    SafePointerType()
        : SafePointerType(Invalid)
    {
    }

    template <typename T = void>
    explicit SafePointerType(T* ptr)
        : SafePointerType(reinterpret_cast<uintptr_t>(ptr))
    {}
    template <typename T = void>
    T* AsPointer() const
    {
        return reinterpret_cast<T*>(this->Get());
    }

    explicit operator bool() const { return *this != Invalid; }
};

template <typename Tag>
const Tag SafePointerType<Tag>::Invalid = {0};

template <typename Tag>
inline bool operator==(const SafePointerType<Tag>& lhs, const SafePointerType<Tag>& rhs)
{
    return lhs.Get() == rhs.Get();
}

template <typename Tag>
inline bool operator!=(const SafePointerType<Tag>& lhs, const SafePointerType<Tag>& rhs)
{
    return lhs.Get() != rhs.Get();
}

} // namespace Details

struct NodeId final : Details::SafePointerType<NodeId> {
    using SafePointerType::SafePointerType;
};

struct LinkId final : Details::SafePointerType<LinkId> {
    using SafePointerType::SafePointerType;
};

struct PinId final : Details::SafePointerType<PinId> {
    using SafePointerType::SafePointerType;
};

//------------------------------------------------------------------------------
} // namespace NodeEditor
} // namespace ax

//------------------------------------------------------------------------------
#endif // __IMGUI_NODE_EDITOR_H__