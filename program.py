import sys
import bisect

num_lines = int(raw_input().split()[1])

sum_store = {}
cum_sum = {}
timestamps = {}

for _ in range(num_lines):
    line = raw_input().split()
    timestamp = int(line[0])
    symbol = line[1]
    line = line[2:]
    for i in range(0, len(line), 2):
        field, value = line[i], int(line[i+1])
        key = (symbol, field)
        if key not in timestamps:
            timestamps[key] = []
        if len(timestamps[key]) == 0 or timestamps[key][-1] != timestamp:
            timestamps[key].append(timestamp)

        if key not in sum_store:
            sum_store[key] = {}
        if key not in cum_sum:
            cum_sum[key] = 0
        if timestamp not in sum_store[key]:
            sum_store[key][timestamp] = cum_sum[key]
        sum_store[key][timestamp] += value
        cum_sum[key] += value

print "tickfile completed"


for line in sys.stdin:
    line = line.split()
    operator = line[0]
    if operator != 'sum':
        print 0
        continue
    key = (line[3], line[4])
    if key not in timestamps:
        print 0
        continue
    lower = bisect.bisect_left(timestamps[key], int(line[1])) - 1
    upper = bisect.bisect_right(timestamps[key], int(line[2])) - 1
#    print 'lower: %d upper %d' % (lower, upper)
    if lower < 0:
        lower_val = 0
    else:
        lower_val = sum_store[key][timestamps[key][lower]]
    print sum_store[key][timestamps[key][upper]] - lower_val
    
    
    
