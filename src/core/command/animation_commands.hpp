#pragma once

#include "base.hpp"

#include "command/base.hpp"
#include "model/animation/animatable.hpp"

namespace command {

class SetKeyframe : public MergeableCommand<Id::SetKeyframe, SetKeyframe>
{
public:
    SetKeyframe(
        model::AnimatableBase* prop,
        model::FrameTime time,
        const QVariant& value,
        bool commit
    );

    void undo() override;

    void redo() override;

    bool merge_with(const SetKeyframe& other);

private:
    model::AnimatableBase* prop;
    model::FrameTime time;
    QVariant before;
    QVariant after;
    bool had_before;
};

class RemoveKeyframeTime : public QUndoCommand
{
public:
    RemoveKeyframeTime(
        model::AnimatableBase* prop,
        model::FrameTime time
    );

    void undo() override;

    void redo() override;

private:
    model::AnimatableBase* prop;
    model::FrameTime time;
    QVariant before;
};


/**
 * \brief Command that sets multiple animated properties at once,
 * setting keyframes based on the document record_to_keyframe
 */
class SetMultipleAnimated : public MergeableCommand<Id::SetMultipleAnimated, SetMultipleAnimated>
{
public:
    SetMultipleAnimated(model::AnimatableBase* prop, QVariant after, bool commit);

    template<class... Args>
    SetMultipleAnimated(
        const QString& name,
        bool commit,
        const std::vector<model::AnimatableBase*>& props,
        Args... vals
    ) : SetMultipleAnimated(name, props, {}, {QVariant::fromValue(vals)...}, commit)
    {}

    /**
     * \pre props.size() == after.size() && (props.size() == before.size() || before.empty())
     *
     * If before.empty() it will be populated by the properties
     */
    SetMultipleAnimated(
        const QString& name,
        const std::vector<model::AnimatableBase*>& props,
        const QVariantList& before,
        const QVariantList& after,
        bool commit
    );

    void undo() override;

    void redo() override;

    bool merge_with(const SetMultipleAnimated& other);

private:
    static QString auto_name(model::AnimatableBase* prop);

    std::vector<model::AnimatableBase*> props;
    QVariantList before;
    QVariantList after;
    std::vector<int> keyframe_before;
    bool keyframe_after;
    model::FrameTime time;
};


class SetKeyframeTransition : public QUndoCommand
{
public:
    SetKeyframeTransition(
        model::AnimatableBase* prop,
        int keyframe_index,
        model::KeyframeTransition::Descriptive desc,
        const QPointF& point,
        bool before_transition
    );

    void undo() override;

    void redo() override;

private:
    model::KeyframeBase* keyframe() const;

    void set_handle(const QPointF& v, model::KeyframeTransition::Descriptive desc) const;

    model::AnimatableBase* prop;
    int keyframe_index;

    QPointF undo_value;
    model::KeyframeTransition::Descriptive undo_desc;

    QPointF redo_value;
    model::KeyframeTransition::Descriptive redo_desc;

    bool before_transition;
};


class MoveKeyframe : public QUndoCommand
{
public:
    MoveKeyframe(
        model::AnimatableBase* prop,
        int keyframe_index,
        model::FrameTime time_after
    );

    void undo() override;

    void redo() override;

private:
    model::AnimatableBase* prop;
    int keyframe_index_before;
    int keyframe_index_after = -1;
    model::FrameTime time_before;
    model::FrameTime time_after;
};


} // namespace command
