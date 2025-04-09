import pexpect


def run_test(addend, accumulator, expected_accumulator, expected_carry):
    cmd = f"./adder {addend} {accumulator}"
    print(f"Running: {cmd}")
    child = pexpect.spawn(cmd)
    child.expect(pexpect.EOF)
    output = child.before.decode().strip()
    print(f"Output:\n{output}\n")
    expected = (
        f"addend=0, accumulator={expected_accumulator}, carry_flag={expected_carry}"
    )
    if expected in output:
        print(f"✅ Test passed for {addend}+{accumulator}\n")
    else:
        print(f"❌ Test failed for {addend}+{accumulator}")
        print(f"Expected: {expected}\n")
        exit(1)


tests = [
    (0, 0, 0, 0),
    (0, 1, 1, 0),
    (1, 0, 1, 0),
    (1, 2, 3, 0),
    (5, 5, 0, 1),
    (9, 1, 0, 1),
    (9, 9, 8, 1),
]

for a, b, acc, carry in tests:
    run_test(a, b, acc, carry)

print("✅ All tests passed.")
