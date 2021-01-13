//
// CONFIDENTIAL - FORD MOTOR COMPANY
//
// This is an unpublished work, which is a trade secret, created in
// 2020.  Ford Motor Company owns all rights to this work and intends
// to maintain it in confidence to preserve its trade secret status.
// Ford Motor Company reserves the right to protect this work as an
// unpublished copyrighted work in the event of an inadvertent or
// deliberate unauthorized publication.  Ford Motor Company also
// reserves its rights under the copyright laws to protect this work
// as a published work.  Those having access to this work may not copy
// it, use it, or disclose the information contained in it without
// the written authorization of Ford Motor Company.
//

/**
 * This is a functional test utility class. The purpose is to
 * offer methods or resources commonly found in soa functional
 * tests.
 */

#ifndef SOA_TEST_UTILS_HPP_
#define SOA_TEST_UTILS_HPP_

#include <array>
#include <sstream>
#include <fstream>
#include <iostream>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <memory>
#include <soa/framework/soa_error_code_util.hpp>


namespace fnv {
namespace soa {
namespace gateway {
namespace functest {


class SoaTestUtils {
    public:
        // drop root for a client
        static void changeUser(uid_t uid);

    private:
        static constexpr const uid_t qnxuser = 1000; //
};

} /* namespace functest */
} /* namespace gateway */
} /* namespace soa */
} /* namespace fnv */

#endif /* SOA_TEST_UTILS_HPP_ */
