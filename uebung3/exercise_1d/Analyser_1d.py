import os

class FloatState:

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
        elif self.state == 4:
            self.state4(elem)
        else:
            return

    def state0(self, elem):
        if str.isdigit(elem) and int(elem) in range(1, 9):
            self.state = 1
        elif elem == 0:
            self.state = 2
        elif elem == ".":
            self.state = 4
        else:
            self.isNotFloat()

    def state1(self, elem):
        if str.isdigit(elem):
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
        if str.isdigit(elem):
            return
        else:
            self.isNotFloat()

    def state4(self, elem):
        if str.isdigit(elem):
            self.state = 3
        else:
            self.isNotFloat


    def isEndState(self):
        if self.state is 3:
            return True
        else:
            return False


posLine = 0
posChar = 0

def analyseFloat(line):
    global posChar
    global posLine
    print "Lexical Analysis of float numbers"
    floatState = FloatState()
    for char in line:
        posChar += 1
        floatState.checkElement(char)
        if floatState.isFloat is False:
            print "The element " + char + " at line " + str(posLine) + \
            " position " + str(posChar) + " is not allowed"
            return False

    return floatState.isEndState()


def main():
    global posLine
    global posChar

    files = [f for f in os.listdir('.') if os.path.isfile(f) and ".txt" in f]
    fileName = ""

    while fileName is "":
        print "choose file by pressing number:"
        for i, item in enumerate(files):
            print str(i + 1) + " -> " + item

        number = raw_input()
        if not str.isdigit(number):
            print "input not valid"
            continue

        if len(files) < int(number) - 1 or int(number) < 1:
            print "file does not exist"
            continue

        fileName = files[int(number) - 1]

    print fileName

    with open(fileName, 'r') as textFile:
        for line in textFile:
            line = line.strip("\n")
            print "Checking " + line + "!"
            posLine += 1
            posChar = 0
            if analyseFloat(line):
                print " => is Float\n"
            else:
                print " => is not Float\n"
            print  " "


if __name__ == "__main__":
    main()
