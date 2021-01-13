#include "publish.h"
#include "gpb/TVF_To_DXP.pb.h"
#include "gpb/TVF_To_DXP_info.pb.h"
#include "gpb/paho_test_utils.h"

//using namespace ford::av::taas;

publish::publish(QObject *parent) : QObject(parent)
{

}

void publish::CancellPullover(bool &temp){
    ford::av::taas::CancelPullover cancellpullover;
    cancellpullover.set_cancel_pullover(temp);
    cancellpullover.SerializeAsString();
    publish()

}
