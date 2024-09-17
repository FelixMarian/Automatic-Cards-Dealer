import sys

from PyQt5.QtCore import QTimer

import Interface_objects
from PyQt5.QtWidgets import *

from UART_communication import GetData

playersSelected = False
cardsNoSelected = False
playersNo = 0
cardsNo = 0


def updateValues(playersNumber, cardsNumber, playerLayouts):
    global playersSelected
    global cardsNoSelected
    global playersNo
    global cardsNo

    receivedMessage = GetData()
    print(receivedMessage)

    if not playersSelected:
        if receivedMessage == 1:
            playersNo += 1
        elif receivedMessage == 2:
            playersNo -= 1
        elif receivedMessage == 3:
            playersSelected = True
        playersNumber.updateNumber(playersNo)
    elif not cardsNoSelected:
        if receivedMessage == 1:
            cardsNo += 1
        elif receivedMessage == 2:
            cardsNo -= 1
        elif receivedMessage == 3:
            cardsNoSelected = True
        cardsNumber.updateNumber(cardsNo)
    else:
        match receivedMessage:
           case "P1":
                ourPlayer = playerLayouts[0]
                ourPlayer.updatePlayerSetted()
           case "P2":
                ourPlayer = playerLayouts[1]
                ourPlayer.updatePlayerSetted()
           case "P3":
                ourPlayer = playerLayouts[2]
                ourPlayer.updatePlayerSetted()
           case "P4":
                ourPlayer = playerLayouts[3]
                ourPlayer.updatePlayerSetted()
           case "P5":
                ourPlayer = playerLayouts[4]
                ourPlayer.updatePlayerSetted()


def main():
    global playerLayouts
    app = QApplication([])
    mainWindow = QWidget()
    mainWindow.setGeometry(100,100,400,600)
    mainWindow.setWindowTitle("Card Dealer Interface")

    # Main layout: the top section and the bottom section
    mainLayout = QVBoxLayout()
    upperLayout = QHBoxLayout()
    bottomLayout = QHBoxLayout()

    # UPPER LAYOUT

    playersNumber = Interface_objects.PlayersNumber()
    cardsNumber = Interface_objects.CardToDeal()

    # Finalizing the upper layout
    upperLayout.addWidget(Interface_objects.CreateVLine())
    upperLayout.addWidget(playersNumber)
    upperLayout.addWidget(Interface_objects.CreateVLine())
    upperLayout.addWidget(cardsNumber)
    upperLayout.addWidget(Interface_objects.CreateVLine())

    # BOTTOM LAYOUT

    # Creating layouts for the 5 players and adding them to a list
    playerLayouts = [
        Interface_objects.PlayerLayout(1),
        Interface_objects.PlayerLayout(2),
        Interface_objects.PlayerLayout(3),
        Interface_objects.PlayerLayout(4),
        Interface_objects.PlayerLayout(5)
    ]

    bottomLayout.addWidget(Interface_objects.CreateVLine())
    for playerLayout in playerLayouts:
        bottomLayout.addWidget(playerLayout)
        bottomLayout.addWidget(Interface_objects.CreateVLine())

    # Recalling the function every 150 ms
    timer = QTimer()
    timer.timeout.connect(lambda: updateValues(playersNumber,cardsNumber,playerLayouts))
    timer.start(150)

    mainLayout.addLayout(upperLayout)
    mainLayout.addWidget(Interface_objects.CreateHLine())
    mainLayout.addLayout(bottomLayout)

    mainWindow.setLayout(mainLayout)
    mainWindow.setStyleSheet("background-color: rgb(22,84,9);")
    mainWindow.show()
    app.exec_()
if __name__ == "__main__":
    main()
