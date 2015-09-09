/****************************************************************************
 * This file is part of Qt AccountsService Addon.
 *
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * Author(s):
 *    Leslie Zhai
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtAccountsService 1.0

Window {
    width: 300; height: 200
    title: "AccountsService Qt binding"

    UserAccount {
        id: userAccount
        Component.onCompleted: {
            faceIcon.source = iconFileName;
            loginName.text = userName;
            realName.text = userAccount.realName;
        }
        onAccountChanged: {
            faceIcon.source = iconFileName;
        }
    }

    Image {
        id: faceIcon
    }

    Text {
        id: loginName
        anchors.left: faceIcon.right
    }

    TextField {
        id: realName
        anchors.top: loginName.bottom
        anchors.left: loginName.left

        onEditingFinished: {
            userAccount.realName = text;
        }
    }
}
