/*
 Copyright (C) AC SOFTWARE SP. Z O.O.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef __SUPLA_ESP_IDF_OTA_H_
#define __SUPLA_ESP_IDF_OTA_H_

#include <supla/device/sw_update.h>
#include <esp_partition.h>
#include <esp_http_client.h>
#include <esp_ota_ops.h>

namespace Supla {

  class EspIdfOta : public Supla::Device::SwUpdate {
    public:
      friend Supla::Device::SwUpdate* Supla::Device::SwUpdate::Create(
          SuplaDeviceClass *sdc, const char* url);
      void start() override;
      void iterate() override;
      bool isFinished() override;
      bool isAborted() override;

    protected:
      bool verifyRsaSignature(const esp_partition_t *update_partition, int binSize);
      void fail(const char *);
      void log(const char *);
      EspIdfOta(SuplaDeviceClass *sdc, const char* newUrl);
      bool finished = false;
      bool abort = false;
      esp_http_client_handle_t client = {};
      esp_ota_handle_t updateHandle = 0;
      uint8_t *otaBuffer = nullptr;
  };
};

#endif /*__SUPLA_ESP_IDF_OTA_H_*/
