/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "sles_allinclusive.h"

/* AudioIODeviceCapabilities implementation */


static SLresult IAudioIODeviceCapabilities_GetAvailableAudioInputs(
    SLAudioIODeviceCapabilitiesItf self, SLint32 *pNumInputs, SLuint32 *pInputDeviceIDs)
{
    SL_ENTER_INTERFACE

    if (NULL == pNumInputs) {
        result = SL_RESULT_PARAMETER_INVALID;
    } else {
        result = SL_RESULT_SUCCESS;
        if (NULL != pInputDeviceIDs) {
            // FIXME should be OEM-configurable
            if (1 > *pNumInputs) {
                result = SL_RESULT_BUFFER_INSUFFICIENT;
            } else {
                pInputDeviceIDs[0] = SL_DEFAULTDEVICEID_AUDIOINPUT;
            }
        }
        *pNumInputs = 1;
    }

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_QueryAudioInputCapabilities(
    SLAudioIODeviceCapabilitiesItf self, SLuint32 deviceID, SLAudioInputDescriptor *pDescriptor)
{
    SL_ENTER_INTERFACE

    if (NULL == pDescriptor) {
        result = SL_RESULT_PARAMETER_INVALID;
    } else {
        result = SL_RESULT_SUCCESS;
        switch (deviceID) {
        // FIXME should be OEM-configurable
        case SL_DEFAULTDEVICEID_AUDIOINPUT:
            *pDescriptor = *AudioInput_id_descriptors[0].descriptor;
            break;
        default:
            result = SL_RESULT_IO_ERROR;
            break;
        }
    }

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_RegisterAvailableAudioInputsChangedCallback(
    SLAudioIODeviceCapabilitiesItf self, slAvailableAudioInputsChangedCallback callback,
    void *pContext)
{
    SL_ENTER_INTERFACE

    IAudioIODeviceCapabilities * this = (IAudioIODeviceCapabilities *) self;
    interface_lock_exclusive(this);
    this->mAvailableAudioInputsChangedCallback = callback;
    this->mAvailableAudioInputsChangedContext = pContext;
    interface_unlock_exclusive(this);
    result = SL_RESULT_SUCCESS;

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_GetAvailableAudioOutputs(
    SLAudioIODeviceCapabilitiesItf self, SLint32 *pNumOutputs, SLuint32 *pOutputDeviceIDs)
{
    SL_ENTER_INTERFACE

    if (NULL == pNumOutputs) {
        result = SL_RESULT_PARAMETER_INVALID;
    } else {
        result = SL_RESULT_SUCCESS;
        if (NULL != pOutputDeviceIDs) {
            // FIXME should be OEM-configurable
            if (2 > *pNumOutputs) {
                result = SL_RESULT_BUFFER_INSUFFICIENT;
                // FIXME if 1 slot available, still fill that
            } else {
                pOutputDeviceIDs[0] = DEVICE_ID_HEADSET;
                pOutputDeviceIDs[1] = DEVICE_ID_HANDSFREE;
                // FIXME SL_DEFAULTDEVICEID_AUDIOOUTPUT?
            }
        }
        *pNumOutputs = 2;
    }

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_QueryAudioOutputCapabilities(
    SLAudioIODeviceCapabilitiesItf self, SLuint32 deviceID, SLAudioOutputDescriptor *pDescriptor)
{
    SL_ENTER_INTERFACE

    if (NULL == pDescriptor) {
        result = SL_RESULT_PARAMETER_INVALID;
    } else {
        result = SL_RESULT_SUCCESS;
        switch (deviceID) {
        // FIXME should be OEM-configurable
        case DEVICE_ID_HEADSET:
            *pDescriptor = *AudioOutput_id_descriptors[1].descriptor;
            break;
        case DEVICE_ID_HANDSFREE:
            *pDescriptor = *AudioOutput_id_descriptors[2].descriptor;
            break;
        // FIXME SL_DEFAULTDEVICEID_AUDIOOUTPUT?
        default:
            result = SL_RESULT_IO_ERROR;
            break;
        }
    }

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_RegisterAvailableAudioOutputsChangedCallback(
    SLAudioIODeviceCapabilitiesItf self, slAvailableAudioOutputsChangedCallback callback,
    void *pContext)
{
    SL_ENTER_INTERFACE

    IAudioIODeviceCapabilities * this = (IAudioIODeviceCapabilities *) self;
    interface_lock_exclusive(this);
    this->mAvailableAudioOutputsChangedCallback = callback;
    this->mAvailableAudioOutputsChangedContext = pContext;
    interface_unlock_exclusive(this);
    result = SL_RESULT_SUCCESS;

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_RegisterDefaultDeviceIDMapChangedCallback(
    SLAudioIODeviceCapabilitiesItf self, slDefaultDeviceIDMapChangedCallback callback,
    void *pContext)
{
    SL_ENTER_INTERFACE

    IAudioIODeviceCapabilities * this = (IAudioIODeviceCapabilities *) self;
    interface_lock_exclusive(this);
    this->mDefaultDeviceIDMapChangedCallback = callback;
    this->mDefaultDeviceIDMapChangedContext = pContext;
    interface_unlock_exclusive(this);
    result = SL_RESULT_SUCCESS;

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_GetAssociatedAudioInputs(
    SLAudioIODeviceCapabilitiesItf self, SLuint32 deviceID,
    SLint32 *pNumAudioInputs, SLuint32 *pAudioInputDeviceIDs)
{
    SL_ENTER_INTERFACE

    if (NULL == pNumAudioInputs) {
        result = SL_RESULT_PARAMETER_INVALID;
    } else {
        // FIXME Incomplete
        *pNumAudioInputs = 0;
        result = SL_RESULT_SUCCESS;
    }

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_GetAssociatedAudioOutputs(
    SLAudioIODeviceCapabilitiesItf self, SLuint32 deviceID,
    SLint32 *pNumAudioOutputs, SLuint32 *pAudioOutputDeviceIDs)
{
    SL_ENTER_INTERFACE

    if (NULL == pNumAudioOutputs) {
        result = SL_RESULT_PARAMETER_INVALID;
    } else {
        // FIXME Incomplete
        *pNumAudioOutputs = 0;
        result = SL_RESULT_SUCCESS;
    }

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_GetDefaultAudioDevices(
    SLAudioIODeviceCapabilitiesItf self, SLuint32 defaultDeviceID,
    SLint32 *pNumAudioDevices, SLuint32 *pAudioDeviceIDs)
{
    SL_ENTER_INTERFACE

    if (NULL == pNumAudioDevices) {
        result = SL_RESULT_PARAMETER_INVALID;
    } else {
        switch (defaultDeviceID) {
        case SL_DEFAULTDEVICEID_AUDIOINPUT:
        case SL_DEFAULTDEVICEID_AUDIOOUTPUT:
            result = SL_RESULT_SUCCESS;
            if (NULL != pAudioDeviceIDs) {
                // FIXME should be OEM-configurable
                switch (defaultDeviceID) {
                case SL_DEFAULTDEVICEID_AUDIOINPUT:
                    if (1 > *pNumAudioDevices) {
                        result = SL_RESULT_BUFFER_INSUFFICIENT;
                    } else {
                        pAudioDeviceIDs[0] = SL_DEFAULTDEVICEID_AUDIOINPUT;
                    }
                    *pNumAudioDevices = 1;
                    break;
                case SL_DEFAULTDEVICEID_AUDIOOUTPUT:
                    if (2 > *pNumAudioDevices) {
                        result = SL_RESULT_BUFFER_INSUFFICIENT;
                    } else {
                        pAudioDeviceIDs[0] = DEVICE_ID_HEADSET;
                        pAudioDeviceIDs[1] = DEVICE_ID_HANDSFREE;
                        // FIXME should be capable of returning first item if 1 slot
                    }
                    *pNumAudioDevices = 2;
                    break;
                default:
                    assert(SL_BOOLEAN_FALSE);
                    *pNumAudioDevices = 0;
                    break;
                }
            }
            break;
        default:
            result = SL_RESULT_IO_ERROR;
            break;
        }
    }

    SL_LEAVE_INTERFACE
}


static SLresult IAudioIODeviceCapabilities_QuerySampleFormatsSupported(
    SLAudioIODeviceCapabilitiesItf self, SLuint32 deviceID, SLmilliHertz samplingRate,
    SLint32 *pSampleFormats, SLint32 *pNumOfSampleFormats)
{
    SL_ENTER_INTERFACE

    if (NULL == pNumOfSampleFormats) {
        result = SL_RESULT_PARAMETER_INVALID;
    } else {
        switch (deviceID) {
        case SL_DEFAULTDEVICEID_AUDIOINPUT:
        case SL_DEFAULTDEVICEID_AUDIOOUTPUT:
            result = SL_RESULT_SUCCESS;
            // FIXME incomplete
            switch (samplingRate) {
            case SL_SAMPLINGRATE_44_1:
                break;
            default:
                result = SL_RESULT_IO_ERROR;
                break;
            }
            if (NULL != pSampleFormats) {
                if (1 > *pNumOfSampleFormats)
                    result = SL_RESULT_BUFFER_INSUFFICIENT;
                // FIXME incomplete
                pSampleFormats[0] = SL_PCMSAMPLEFORMAT_FIXED_16;
            }
            *pNumOfSampleFormats = 1;
            break;
        default:
            result = SL_RESULT_IO_ERROR;
            break;
        }
    }

    SL_LEAVE_INTERFACE
}


static const struct SLAudioIODeviceCapabilitiesItf_ IAudioIODeviceCapabilities_Itf = {
    IAudioIODeviceCapabilities_GetAvailableAudioInputs,
    IAudioIODeviceCapabilities_QueryAudioInputCapabilities,
    IAudioIODeviceCapabilities_RegisterAvailableAudioInputsChangedCallback,
    IAudioIODeviceCapabilities_GetAvailableAudioOutputs,
    IAudioIODeviceCapabilities_QueryAudioOutputCapabilities,
    IAudioIODeviceCapabilities_RegisterAvailableAudioOutputsChangedCallback,
    IAudioIODeviceCapabilities_RegisterDefaultDeviceIDMapChangedCallback,
    IAudioIODeviceCapabilities_GetAssociatedAudioInputs,
    IAudioIODeviceCapabilities_GetAssociatedAudioOutputs,
    IAudioIODeviceCapabilities_GetDefaultAudioDevices,
    IAudioIODeviceCapabilities_QuerySampleFormatsSupported
};

void IAudioIODeviceCapabilities_init(void *self)
{
    IAudioIODeviceCapabilities *this = (IAudioIODeviceCapabilities *) self;
    this->mItf = &IAudioIODeviceCapabilities_Itf;
    this->mAvailableAudioInputsChangedCallback = NULL;
    this->mAvailableAudioInputsChangedContext = NULL;
    this->mAvailableAudioOutputsChangedCallback = NULL;
    this->mAvailableAudioOutputsChangedContext = NULL;
    this->mDefaultDeviceIDMapChangedCallback = NULL;
    this->mDefaultDeviceIDMapChangedContext = NULL;
}
