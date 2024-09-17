from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import *

def CreateVLine():
    # Vertical separator lines
    lineVerticalUpper = QFrame()
    lineVerticalUpper.setFrameShape(QFrame.VLine)
    lineVerticalUpper.setFrameShadow(QFrame.Sunken)
    return lineVerticalUpper

def CreateHLine():
    # Horizontal separator lines
    lineHorizontal = QFrame()
    lineHorizontal.setFrameShape(QFrame.HLine)
    lineHorizontal.setFrameShadow(QFrame.Sunken)
    return lineHorizontal

class PlayersNumber(QWidget):
    def __init__(self):
        super().__init__()
        self.layout = QVBoxLayout()
        self.playerNo_text = QLabel("Number of players")
        self.playerNo_number = QLabel("0")

        self.playerNo_number.setFont(QFont("Arial", 40))
        self.playerNo_number.setStyleSheet("background-color: rgb(255,255,255);")
        self.playerNo_number.setAlignment(Qt.AlignCenter)
        self.playerNo_text.setAlignment(Qt.AlignCenter)

        self.playerNo_text.setFont(QFont("Arial", 20))
        self.layout.addWidget(self.playerNo_text)
        self.layout.addWidget(self.playerNo_number)
        self.setLayout(self.layout)

    def updateNumber(self, number):
        self.playerNo_number.setText(str(number))

class CardToDeal(QWidget):
    def __init__(self):
        super().__init__()
        self.layout = QVBoxLayout()
        self.cardsTD_text = QLabel("Number of card to be dealt")
        self.cardsTD_number = QLabel("0")

        self.cardsTD_number.setFont(QFont("Arial", 40))
        self.cardsTD_number.setStyleSheet("background-color: rgb(255,255,255);")
        self.cardsTD_number.setAlignment(Qt.AlignCenter)

        self.cardsTD_text.setFont(QFont("Arial", 20))
        self.cardsTD_text.setAlignment(Qt.AlignCenter)

        self.layout.addWidget(self.cardsTD_text)
        self.layout.addWidget(self.cardsTD_number)
        self.setLayout(self.layout)

    def updateNumber(self, number):
        self.cardsTD_number.setText(str(number))

# Creating widget for Player
class PlayerLayout(QWidget):
    def __init__(self, playerNo):
        super().__init__()
        self.layout = QVBoxLayout()
        self.playerNo_text = QLabel(f"Player {playerNo}")
        self.playerNo_setted = QLabel("NOT")

        self.playerNo_text.setFont(QFont("Arial", 20))
        self.playerNo_text.setAlignment(Qt.AlignCenter)

        self.playerNo_setted.setFont(QFont("Arial", 40))
        self.playerNo_setted.setAlignment(Qt.AlignCenter)
        self.playerNo_setted.setStyleSheet("color: red")

        self.layout.addWidget(self.playerNo_text)
        self.layout.addWidget(self.playerNo_setted)
        self.setLayout(self.layout)

    def updatePlayerSetted(self):
        self.playerNo_setted.setText("OK")
        self.playerNo_setted.setFont(QFont("Arial", 40))
        self.playerNo_setted.setStyleSheet("color: green")
