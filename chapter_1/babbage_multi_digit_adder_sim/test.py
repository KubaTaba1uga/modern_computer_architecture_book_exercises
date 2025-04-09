import pexpect


def normalize_result(s):
    return s.lstrip("0") or "0"


def run_test(addend, accumulator, expected_result):
    cmd = f"./adder {addend} {accumulator}"
    print(f"Running: {cmd}")
    child = pexpect.spawn(cmd)
    child.expect(pexpect.EOF)
    output = child.before.decode().strip()
    print(f"Output:\n{output}\n")

    # Extract result after "=== FINISH ==="
    lines = output.splitlines()
    result_line = ""
    for i, line in enumerate(lines):
        if line.startswith("=== FINISH ==="):
            result_line = lines[i + 1]
            break

    if not result_line.startswith("accumulators: "):
        print(f"❌ Could not find result in output")
        exit(1)

    result = result_line.split(": ")[1]
    result = normalize_result(result)
    expected = normalize_result(str(expected_result))

    if result == expected:
        print(f"✅ Test passed: {addend} + {accumulator} = {expected}\n")
    else:
        print(
            f"❌ Test failed: {addend} + {accumulator} = {result}, expected {expected}\n"
        )
        exit(1)


tests = [
    ("0", "0", 0),
    ("0", "1", 1),
    ("1", "0", 1),
    ("1", "2", 3),
    ("5", "5", 10),
    ("9", "1", 10),
    ("9", "9", 18),
    ("99", "1", 100),
    ("9999", "1", 10000),
    ("49", "50", 99),
    ("50", "50", 100),
]

for a, b, expected in tests:
    run_test(a, b, expected)

print("✅ All test cases passed.")
