/* Copyright (c) 2020 The Khronos Group Inc.
 * Copyright (c) 2020 Valve Corporation
 * Copyright (c) 2020 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Mark Lobodzinski <mark@lunarg.com>
 */

#pragma once
#include "vulkan/vulkan.h"

// VK_EXT_layer_settings
//
// Name String
//   VK_EXT_layer_settings
//
// Extension Type
//   Instance extension
//
// Revision
//    1
//
// Extension and Version Dependencies
//    Requires Vulkan 1.0
//
// Contact
//    Mark Lobodzinski mark-lunarg
//
// Description
//    This extension provides the VkInstanceLayerSettingsEXT struct that can be included in the pNext chain of the
//    VkInstanceCreateInfo structure passed as the pCreateInfo parameter of vkCreateInstance
//        The structure contains an array of VkLayerSettingValueEXT structures that define layer specific settings
//    The extension also provides the vkEnumerateInstanceLayerSettingsEXT and vkEnumerateInstanceLayerSettingInfoEXT
//    commands, useful for enumerating all layer settings and their possible values, respectively.
//
// Note
//    The VK_EXT_layer_settings extension subsumes all the functionality provided in the [VK_EXT_validation_flags] extension
//    and the [VK_EXT_validation_features] extension.
//
// New Commands
//    vkEnumerateInstanceLayerSettingsEXT
//    vkEnumerateInstanceLayerSettingInfoEXT
//
// New Structures
//    VkLayerSettingValueEXT
//    VkLayerSettingDescriptionEXT
//    VkLayerSettingOptionEXT
//    Extending VkInstanceCreateInfo :
//        VkInstanceLayerSettingsEXT
//
// New Unions
//    VkLayerSettingValueDataEXT
//
// New Enums
//    VkLayerSettingValueTypeEXT

#define VK_EXT_layer_settings 1
#define VK_EXT_LAYER_SETTINGS_SPEC_VERSION 1
#define VK_EXT_LAYER_SETTINGS_EXTENSION_NAME "VK_EXT_layer_settings"

// These stype values were selected to prevent interference with Vulkan spec definitions
static const uint32_t VK_STRUCTURE_TYPE_INSTANCE_LAYER_SETTINGS_EXT = 3000300003;
static const uint32_t VK_STRUCTURE_TYPE_LAYER_SETTING_VALUE_EXT = 3000300004;
static const uint32_t VK_STRUCTURE_TYPE_LAYER_SETTING_DESCRIPTION_EXT = 3000300005;
static const uint32_t VK_STRUCTURE_TYPE_LAYER_SETTING_OPTION_EXT = 3000300006;

typedef enum VkLayerSettingValueTypeEXT {
    VK_LAYER_SETTING_VALUE_TYPE_UINT32_EXT = 0,
    VK_LAYER_SETTING_VALUE_TYPE_UINT64_EXT = 1,
    VK_LAYER_SETTING_VALUE_TYPE_FLOAT_EXT = 2,
    VK_LAYER_SETTING_VALUE_TYPE_BOOL_EXT = 3,
    VK_LAYER_SETTING_VALUE_TYPE_STRING_EXT = 4,
} VkLayerSettingValueTypeEXT;

typedef union VkLayerSettingValueDataEXT {
    uint32_t value32;
    uint64_t value64;
    float valueFloat;
    VkBool32 valueBool;
    const char* valueString;
} VkLayerSettingValueDataEXT;

typedef struct VkLayerSettingValueEXT {
    VkStructureType sType;
    void* pNext;
    char settingName[VK_MAX_EXTENSION_NAME_SIZE];
    VkLayerSettingValueTypeEXT type;
    VkLayerSettingValueDataEXT data;
} VkLayerSettingValueEXT;

typedef struct VkInstanceLayerSettingsEXT {
    VkStructureType sType;
    void* pNext;
    uint32_t settingCount;
    VkLayerSettingValueEXT* pSetting;
} VkInstanceLayerSettingsEXT;

typedef struct VkLayerSettingDescriptionEXT {
    VkStructureType sType;
    void* pNext;
    char settingName[VK_MAX_EXTENSION_NAME_SIZE];
    VkLayerSettingValueTypeEXT type;
    char description[VK_MAX_DESCRIPTION_SIZE];
    char default_value[VK_MAX_DESCRIPTION_SIZE];
} VkLayerSettingDescriptionEXT;

typedef struct VkLayerSettingOptionEXT {
    VkStructureType sType;
    void* pNext;
    char optionName[VK_MAX_EXTENSION_NAME_SIZE];
    char description[VK_MAX_DESCRIPTION_SIZE];
} VkLayerSettingOptionEXT;

VkResult vkEnumerateInstanceLayerSettingsEXT(const char* pLayerName, uint32_t* pSettingCount,
                                             VkLayerSettingDescriptionEXT* pSettings);

VkResult vkEnumerateInstanceLayerSettingInfoEXT(const char* pLayerName, const char* pSettingName, uint32_t* pSettingInfoCount,
                                                VkLayerSettingOptionEXT* pSettingOptions);
