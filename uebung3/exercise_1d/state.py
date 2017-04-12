class State:

    name = "Float State"

    def __init__(self):
        self.state = 0
        self.isFloat = True

    def incState(self):
        self.state += 1

    def isNotFloat(self):
        self.state = -1
        self.isFloat = False

    def checkElement(self, elem):
        if self.state == 0:
            self.state0(elem)
        elif self.state == 1:
            self.state1(elem)
        elif self.state == 2:
            self.state2(elem)
        elif self.state == 3:
            self.state3(elem)
        else:
            return

    def state0(self, elem):
        if elem in range(1,9):
            self.state = 1
        elif elem == 0:
            self.state = 2
        elif elem == ".":
            self.state -= 3
        else:
            self.isNotFloat()

    def state1(self, elem):
        if elem in range(0, 9):
          return
        elif elem == ".":
            self.state = 3
        else:
            self.isNotFloat()

    def state2(self, elem):
        if elem == ".":
            self.state = 3
        else:
            self.isNotFloat()
    
    def state3(self, elem):
        if str.isdigit:
            return
        else:
            self.isNotFloat()