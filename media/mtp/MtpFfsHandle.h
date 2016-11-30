/*
 * Copyright (C) 2016 The Android Open Source Project
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

#ifndef _MTP_FFS_HANDLE_H
#define _MTP_FFS_HANDLE_H

#include <IMtpHandle.h>

namespace android{
class MtpFfsHandleTest;
}

namespace {

class MtpFfsHandle : public IMtpHandle {
    friend class android::MtpFfsHandleTest;
private:
    int writeHandle(int fd, const void *data, int len);
    int readHandle(int fd, void *data, int len);
    int spliceReadHandle(int fd, int fd_out, int len);
    bool initFunctionfs();
    void closeConfig();
    void closeEndpoints();

    bool mPtp;

    std::mutex mLock;

    int mControl;
    int mBulkIn;  /* "in" from the host's perspective => sink for mtp server */
    int mBulkOut; /* "out" from the host's perspective => source for mtp server */
    int mIntr;

public:
    int read(void *data, int len);
    int write(const void *data, int len);

    int receiveFile(mtp_file_range mfr);
    int sendFile(mtp_file_range mfr);
    int sendEvent(mtp_event me);

    int start();
    int close();

    int configure(bool ptp);

    MtpFfsHandle();
    ~MtpFfsHandle();
};

struct mtp_data_header {
    /* length of packet, including this header */
    __le32 length;
    /* container type (2 for data packet) */
    __le16 type;
    /* MTP command code */
    __le16 command;
    /* MTP transaction ID */
    __le32 transaction_id;
};

} // anonymous namespace

#endif // _MTP_FF_HANDLE_H

