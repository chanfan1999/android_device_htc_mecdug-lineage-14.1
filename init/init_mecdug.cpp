/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void common_properties()
{
    property_set("rild.libargs", "-d /dev/smd0");
    property_set("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420,23594,27202,27205");
    property_set("ro.ril.enable.a52", "0");
    property_set("ro.ril.enable.a53", "1");
    property_set("ro.ril.enable.pre_r8fd", "1");
    property_set("ro.ril.enable.r8fd", "1");
    property_set("ro.ril.telephony.mqanelements", "5");
}

void dualsim_properties(char const multisim_config[])
{
    property_set("persist.radio.multisim.config", multisim_config);
    property_set("persist.radio.dont_use_dsd", "true");
    property_set("ro.multisim.set_audio_params", "true");
    property_set("ro.telephony.ril.config", "simactivation,sim2gsmonly");
}

void cdma_properties(char const default_cdma_sub[], char const default_network[])
{
    property_set("ro.telephony.default_cdma_sub", default_cdma_sub);
    property_set("ro.telephony.default_network", default_network);

    property_set("ro.ril.oem.ecclist", "110,112,119,120,911,999");
    property_set("ro.ril.oem.normalcall.ecclist", "110,119,120,999");
    property_set("ro.ril.oem.nosim.ecclist", "110,112,119,120,911,999,08,000,118,122");
    property_set("ro.ril.gprsclass", "10");
    property_set("ro.ril.set.mtusize", "1420");

    property_set("telephony.lteOnCdmaDevice", "1");
    property_set("ro.ril.hsdpa.category", "10");
    property_set("ro.ril.hsxpa", "2");
    property_set("ro.ril.enable.sdr", "0");
    property_set("ro.ril.disable.sync_pf", "1");
}

void gsm_properties(char const default_network[])
{
    property_set("ro.telephony.default_network", default_network);

    property_set("telephony.lteOnGsmDevice", "1");
    property_set("ro.ril.hsdpa.category", "24");
    property_set("ro.ril.hsxpa", "4");
    property_set("ro.ril.disable.cpc", "1");
    property_set("ro.ril.enable.sdr", "1");
    property_set("ro.ril.fast.dormancy.rule", "1");
}

void vendor_load_properties()
{
    std::string platform;
    std::string bootmid;
    std::string device;

    platform = property_get("ro.board.platform");
    if (platform != ANDROID_TARGET)
        return;

    bootmid = property_get("ro.boot.mid");

    if (bootmid == "0PAJ20000") {
        /* m8dug (china unicom) */
        common_properties();
        dualsim_properties("dsds");
        gsm_properties("9,1");
        property_set("ro.product.model", "HTC M8sw");
        property_set("ro.ril.ltefgi", "1594883712");
        property_set("ro.build.fingerprint", "htc/htccn_chs_cu/htc_mecdug:5.0.2/LRX22G/480430.6:user/release-keys");
        property_set("ro.build.description", "4.25.1402.6 CL480430 release-keys");
        property_set("ro.product.device", "htc_mecdug");
        property_set("ro.build.product", "htc_mecdug");
    }

    device = property_get("ro.product.device");
    ERROR("Found bootmid %s setting build properties for %s device\n", bootmid.c_str(), device.c_str());
}
