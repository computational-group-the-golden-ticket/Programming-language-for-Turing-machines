TuringMachine Zero:
	"q0" "1" "0" "q1"
	"q1" "0" "R" "q0"

test_tape = ("1" "1" "1" "1" "1")

result_tape1 = Zero test_tape

PRINT result_tape1
