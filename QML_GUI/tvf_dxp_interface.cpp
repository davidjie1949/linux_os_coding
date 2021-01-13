#include "tvf_dxp_interface.h"
#include "gpb/TVF_To_DXP.pb.h"
#include "gpb/TVF_To_DXP_info.pb.h"
#include "gpb/paho_test_utils.h"

tvf_dxp_interface::tvf_dxp_interface(QObject *parent) : QObject(parent)
{

}

void tvf_dxp_interface::CancellPullover(bool &temp){
    const string CLIENTID       = "DXPPub";
    const string TOPIC          = "/SERVICE/REQUEST/AVPIM/SDM/PASSENGERPULLOVER";
    const int QOS               =  0;
    const unsigned int TIMEOUT  = 10000L;

    string binary;
    CancelPullover cancellpullover;
    cancellpullover.set_cancel_pullover(temp);
    cancellpullover.SerializeToString(&binary);
    publish(binary, CLIENTID, TOPIC, QOS, TIMEOUT);

}
