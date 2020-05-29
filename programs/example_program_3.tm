TuringMachine Zero:
	"q0" "1" "0" "q1"
	"q1" "0" "R" "q0"

TuringMachine Succesor:
	"q0" "1" "R" "q1"
	"q0" "0" "1" "q1"

test_tape1 = ("1" "1" "1" "1" "1")
test_tape2 = ("1" "1") test_tape1

result_tape1 = test_tape1 Succesor Zero test_tape with (1 "q1" "1") with (1 "q1" "1")

PRINT result_tape1
