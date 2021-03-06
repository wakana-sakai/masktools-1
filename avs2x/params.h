#ifndef __Common_Avs2x_Params_H__
#define __Common_Avs2x_Params_H__

#include "clip.h"
#include "../common/params/params.h"

namespace Filtering { namespace Avisynth2x {

static Value AVSValueToValue(const AVSValue& value, const Parameter &param)
{
    switch (param.getType())
    {
    case TYPE_INT: return Value(value.AsInt());
    case TYPE_STRING: return Value(String(value.AsString()));
    case TYPE_BOOL: return Value(value.AsBool());
    case TYPE_CLIP: return std::shared_ptr<Filtering::Clip>(new Clip(value.AsClip()));
    case TYPE_FLOAT: return Value(value.AsFloat());
    default: return Value();
    }
}

static String ParameterToString(const Parameter &parameter)
{
    String str = "";

    if (parameter.isNamed())
        str.append("[").append(parameter.getName()).append("]");

    switch (parameter.getType())
    {
    case TYPE_INT: return str.append("i");
    case TYPE_FLOAT: return str.append("f");
    case TYPE_STRING: return str.append("s");
    case TYPE_CLIP: return str.append("c");
    case TYPE_BOOL: return str.append("b");
    default: assert(0); return "";
    }
}

String SignatureToString(const Signature &signature)
{
    String str;

    for (int i = 0; i < signature.count(); i++) {
        str.append(ParameterToString(signature[i]));
    }

    return str;
}

Parameter GetParameter(const AVSValue &value, const Parameter &default_param)
{
    if (value.Defined()) {
        return Parameter(AVSValueToValue(value, default_param), default_param.getName());
    }

    Parameter parameter = default_param;
    parameter.set_defined(false);

    return parameter;
}

Parameters GetParameters(const AVSValue &args, const Signature &signature, IScriptEnvironment *env)
{
    Parameters parameters;

    UNUSED(env);

    for (int i = 0; i < signature.count(); i++) {
        parameters.push_back(GetParameter(args[i], signature[i]));
    }

    return parameters;
}

} }

#endif
