import State


posLine = 0
posChar = 0

def analyseFloat(line):
    global posChar
    global posLine
    print "Lexical Analysis of float numbers"
    floatState = State.FloatState()
    for char in line:
        posChar += 1
        floatState.checkElement(char)
        if floatState.isFloat == False:
            print "The element " + char + " at line " + str(posLine) + " posiition " + str(posChar) + " is not allowed"
            return False
    
    return floatState.isEndState()


def main():
    global posLine
    global posChar
    with open('floatnumber.txt', 'r') as textFile:
        for line in textFile:
            line = line.strip("\n")
            print "Checking " + line + "!"
            posLine += 1
            posChar = 0
            if analyseFloat(line):
                print " => is Float"
            else:
                print " => is not Float"


if __name__ == "__main__":
    main()
