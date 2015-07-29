

import QtQuick 2.2
import QtQuick.Window 2.1
import QtAccountsService 1.0

Window {
    width: 300; height: 200
    title: "AccountsService Qt binding"

    UserAccount {
        id: userAccount
        Component.onCompleted: {
            faceIcon.source = iconFileName;
            loginName.text = userName;
            displayName.text = userAccount.displayName;
        }
    }

    Image {
        id: faceIcon
    }

    Text {
        id: loginName
        anchors.left: faceIcon.right
    }

    Text {
        id: displayName
        anchors.top: loginName.bottom
        anchors.left: loginName.left
    }
}
