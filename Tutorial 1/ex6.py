import re
import sys
regex = re.compile("^([A-z]+) ([A-z]+)")
with open(sys.argv[1], 'r') as random_names:
    for line in random_names:
        print(regex.search(line).group(2), regex.search(line).group(1))
