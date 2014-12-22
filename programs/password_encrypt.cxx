/**
 * Copyright (C) 2014 Virgil Security Inc.
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *     (3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>

#include <virgil/VirgilByteArray.h>
using virgil::VirgilByteArray;

#include <virgil/service/VirgilCipher.h>
using virgil::service::VirgilCipher;

#include <virgil/service/VirgilCipherDatagram.h>
using virgil::service::VirgilCipherDatagram;

int print_usage(std::ostream& out, const char *programName) {
    out << "Usage: " << programName << " <data> <pwd> <enc_data>" << std::endl;
    out << "    <data>     - [in]  string to be encrypted" << std::endl;
    out << "    <pwd>      - [in]  password" << std::endl;
    out << "    <enc_data> - [out] encrypted data file" << std::endl;
    return -1;
}

int main(int argc, char **argv) {
    // Parse arguments.
    const char *programName = argv[0];
    unsigned currArgPos = 0;

    // Check arguments num.
    if (argc < 4) {
        return print_usage(std::cerr, programName);
    }

    // Parse argument: data
    ++currArgPos;
    VirgilByteArray data = VIRGIL_BYTE_ARRAY_FROM_STD_STRING(std::string(argv[currArgPos]));

    // Parse argument: pwd
    ++currArgPos;
    VirgilByteArray password = VIRGIL_BYTE_ARRAY_FROM_STD_STRING(std::string(argv[currArgPos]));

    // Parse argument: enc_data
    ++currArgPos;
    std::ofstream encryptedDataFile(argv[currArgPos], std::ios::out | std::ios::binary);
    if (!encryptedDataFile.is_open()) {
        std::cerr << "Unable to open file: " <<  argv[currArgPos] << std::endl;
        return print_usage(std::cerr, programName);
    }

    // Create cipher.
    VirgilCipher cipher;

    // Encrypt data.
    VirgilByteArray encryptedData = cipher.encryptWithPassword(data, password);

    // Write encrypted data to file.
    std::copy(encryptedData.begin(), encryptedData.end(), std::ostreambuf_iterator<char>(encryptedDataFile));

    return 0;
}
