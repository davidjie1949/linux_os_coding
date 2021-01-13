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

#include "soa-test-utils.hpp"

namespace fnv {
namespace soa {
namespace gateway {
namespace functest {

/**
 * changeUser Function
 * dropping root permissions to become user with UID, this method
 * also adds the soa_client group to the user for the run of this process
 * to allow the test to run regardless of the UDS mode being strict or all
 * or anything in between.
 */
void SoaTestUtils::changeUser(uid_t UID) {

    gid_t GID = UID;  //use input UID
    std::unique_ptr<gid_t[]> suppGroups;
    int gidsize = 3; // own gid, soa_client and qnxuser

    struct passwd pw;
    //constexpr size_t passwdStructSize = 64;
    std::array<char, 64> buffer;
    struct passwd *result1;
    getpwuid_r(UID, &pw, buffer.data(), buffer.size(), &result1);
    
    gid_t soa_client_gid;

    struct group   grp;
    struct group * result;
    //constexpr size_t safeBufferSize = 2048;
    std::array<char,2048> buffer1;
    getgrnam_r("soa_client", &grp, buffer1.data(), buffer1.size(), &result);
    if ( result ) {
        soa_client_gid = grp.gr_gid;
    } else {
        std::cerr << ("Warning: group not found in /etc/group file, set to UID\n");
        soa_client_gid = UID;
    }

    if( result1 ) {
        if(initgroups(pw.pw_name, UID)) {
            std::cerr << "Warning: initgroups failed. Test may fail." << std::endl;
            suppGroups = std::unique_ptr<gid_t[]>(new gid_t[gidsize]);
            int c = 0;
            suppGroups[c] = UID;
            suppGroups[++c] = soa_client_gid;
            suppGroups[++c] = qnxuser;
        } else {
            // everything should work for UDS
            // the user is known and the soa_client and qnxuser groups will be added to it
            gidsize = getgroups(0, nullptr);
            if (gidsize < 0) {  // adjust for the error and keep going
                gidsize = 0;
            }
            suppGroups = std::unique_ptr<gid_t[]>(new gid_t[gidsize + 1 + 1]);
            if( getgroups(gidsize, &suppGroups[0]) < 0 ) {
                std::cerr << "Warning: Error "<< errno <<" reported while getting groups." << std::endl;
                gidsize = 0;
            }
            int notSoaClients = 0;
            int notQnxUsers = 0;
            for(int i = 0; i < gidsize; i++) {
                if (suppGroups[i] != soa_client_gid) {
                    ++ notSoaClients;
                }
                if (suppGroups[i] != qnxuser) {
                    ++ notQnxUsers;
                }
            }
            int startingGidCount = gidsize;
            if (notSoaClients == startingGidCount) {
                suppGroups[gidsize] = soa_client_gid;
                ++ gidsize;
            }
            if (notQnxUsers == startingGidCount) {
                suppGroups[gidsize] = qnxuser;
                ++ gidsize;
            }
        }
    } else {
        // UDS strict mode will fail for this because the user is not known
        std::cerr << "Warning: UID " << UID << " not known in the system. Test may fail." << std::endl;
        suppGroups = std::unique_ptr<gid_t[]>(new gid_t[gidsize]);
        int c = 0;
        suppGroups[c] = UID;
        suppGroups[++c] = soa_client_gid;
        suppGroups[++c] = qnxuser;
    }
    setgroups(gidsize, &suppGroups[0]);
    if ( setgid(GID) ) {
        std::cerr << "Error: Cannot set GID to " << GID << std::endl;
    }
    if ( setuid(UID) ) {
        std::cerr << "Error: Cannot set UID to " << UID << std::endl;
    } else {
        std::cout << "drop root to uid [" << UID << "] complete" << std::endl;
    }
}

} /* namespace functest */
} /* namespace gateway */
} /* namespace soa */
} /* namespace fnv */