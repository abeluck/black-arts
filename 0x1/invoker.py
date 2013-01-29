import subprocess
import sys


p = subprocess.Popen(["./server"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)

p.wait()

wizard = sys.stdin.read(1169)
p.stdin.write(wizard)

while True:
    output = p.stdout.readline()
    if output == '':
        break
    print("Partner said: %s" % (output.strip()))

