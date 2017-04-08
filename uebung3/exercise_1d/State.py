class FloatState:

    name = "Float State"

    def __init__(self):
        self.state = 0
        self.isFloat = True

    def resetState(self):
        self.state = 0
        self.isFloat = True

    def isEndState(self):
        if self.state != 4:
            return False
        return True

    def setNotFloat(self):
        self.state = -1
        self.isFloat = False

    def checkElement(self, elem):
        print "Check: " + elem

        try:
            elem = int(elem)
        except ValueError:
            if not elem == ".":
                self.setNotFloat()
                return

        if self.state == 0:
            self.state0(elem)
        elif self.state == 1:
            self.state1(elem)
        elif self.state == 2:
            self.state2(elem)
        elif self.state == 3:
            self.state3(elem)
        elif self.state == 4:
            self.state4(elem)
        else:
            return

    def state0(self, elem):
        if elem in range(1,9):
            self.state = 1
        elif elem == 0:
            self.state = 2
        elif elem == ".":
            self.state = 3
        else:
            self.setNotFloat()

    def state1(self, elem):
        if elem in range(0, 9):
          return
        elif elem == ".":
            self.state = 4
        else:
            self.setNotFloat()

    def state2(self, elem):
        if elem == ".":
            self.state = 4
        else:
            self.setNotFloat()

    def state3(self, elem):
        self.state = 4


    def state4(self, elem):
        if elem == ".":
            self.setNotFloat()