//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/base/vt/wrapArray.h"

#include "pxr/usd/sdf/assetPath.h"

#include "pxr/base/tf/registryManager.h"
#include "pxr/base/tf/staticTokens.h"
#include "pxr/base/tf/type.h"

#include "pxr/base/vt/array.h"
#include "pxr/base/vt/value.h"

#include <iostream>

// Register this class with the TfType registry
// Array registration included to facilitate Sdf/Types and Sdf/ParserHelpers
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<SdfAssetPath>();
    TfType::Define< VtArray<SdfAssetPath> >();
}

TF_REGISTRY_FUNCTION(VtValue)
{
    VtValue::RegisterSimpleCast<std::string, SdfAssetPath>();
    VtRegisterValueCastsFromPythonSequencesToArray<SdfAssetPath>();
}

TF_DEFINE_PRIVATE_TOKENS(
    _tokens,
    ((enclosure, "@"))      // Used to open and close the asset path string.
);

SdfAssetPath::SdfAssetPath()
{
}

SdfAssetPath::SdfAssetPath(const std::string &path)
    : _assetPath(path)
{
}

SdfAssetPath::SdfAssetPath(const std::string &path,
                           const std::string &resolvedPath)
    : _assetPath(path)
    , _resolvedPath(resolvedPath)
{
}

bool
SdfAssetPath::operator<(const SdfAssetPath &rhs) const
{
    if (_assetPath < rhs._assetPath)
        return true;
    if (rhs._assetPath < _assetPath)
        return false;

    return _resolvedPath < rhs._resolvedPath;
}

std::ostream& 
operator<<(std::ostream& out, const SdfAssetPath& ap)
{
    return out << _tokens->enclosure << ap.GetAssetPath() << _tokens->enclosure;
}
