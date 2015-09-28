import sys
import bisect
from collections import defaultdict
from functools import partial
import copy
import math

num_lines = int(raw_input().split()[1])

sum_store = {}
cum_sum = {}
timestamps = {}
lines = []

'''
Read Ticks
'''
for _ in range(num_lines):
    lines.append(raw_input().split())
'''
Product Query
Assumption: Number of fields will not be large as 
Approach: Saving prefix sum of products of all possible field pairs till a timestamp and then differnce of that between two timestamps of a symbol and a field will give sum of product between those timestamps.
Complexity:
Time : Constant Time O(1)
Space : O(F*F*S*N) F -> Number of Fields S -> Number of Symbols N-> Number of Timestamps  
'''
def product():
    for line in lines:
        timestamp = int(line[0])
        symbol = line[1]
        line = line[2:]
        fields= {}

        for i in range(0, len(line), 2):
            fields[line[i]] = int(line[i+1])

        for f in fields.keys():
            for f2 in fields.keys():
                if f > f2:
                    continue
                key = (symbol, f, f2)
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
                sum_store[key][timestamp] += fields[f] * fields[f2]
                cum_sum[key] += fields[f] * fields[f2]

'''
Sum Query 
Approach: Saving prefix sum of all possible fields till a timestamp and then difference of that between two timestamps of a symbol and a field will give sum  between those timestamps.
Complexity:
Time : Constant Time O(1)
Space : O(F*S*N) F -> Number of Fields S -> Number of Symbols N-> Number of Timestamps  
'''             
def my_sum():
    for line in lines:
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
'''
Max Query 
Approach: Saving a ordered set of value vs count of that value (Naming "Bin"). A cumulative bin is maintained till time t and then bins are subtracted to get a bin which is an ordered set of (Value->Count) for a time range. This set is then printed till k in k time since it is ordered with each value being printed as many as Count of that value.
Complexity: 
Time : Constant Time O(k)
Space : O(F*S*N) F -> Number of Fields S -> Number of Symbols N-> Number of Timestamps  
'''         
def largest_k(queries):
    counts = {}
    cum_sum = {}
    for line in lines:
        timestamp = int(line[0])
        symbol = line[1]
        line = line[2:]
        for i in range(0, len(line), 2):
            field, value = line[i], int(line[i+1])
            key = (symbol, field)
            #print 'key: ', key
            if key not in timestamps:
                timestamps[key] = []
            if len(timestamps[key]) == 0 or timestamps[key][-1] != timestamp:
                timestamps[key].append(timestamp)
            if key not in counts:
                counts[key] = {}
            if timestamp not in counts[key]:
                if key not in cum_sum:
                    cum_sum[key] = {}
                counts[key][timestamp] = copy.deepcopy(cum_sum[key])
            if value not in cum_sum[key]:
                cum_sum[key][value] = 0
            if value not in counts[key][timestamp]:
                counts[key][timestamp][value] = copy.deepcopy(cum_sum[key][value])
            counts[key][timestamp][value] += 1
            #print 'counts: ', counts
            cum_sum[key][value] += 1
    for q in queries:
        key = (q[3], q[4])
        #print 'timestamps[key]: ', timestamps[key]
        lower = bisect.bisect_left(timestamps[key], int(q[1])) - 1
        upper = bisect.bisect_right(timestamps[key], int(q[2])) - 1
        if key not in timestamps:
            print
            continue
        if lower < 0:
            lower_val = 0
        else:
            lower = timestamps[key][lower]
            lower_val = -1
        upper = timestamps[key][upper]
        #print 'upper: ', upper
        #print 'lower: ', lower
        candidate_keys = sorted(counts[key][upper].keys(), reverse=True)
        k = int(q[-1])
        top_k = []

        #print 'counts[key]: ', counts[key]
        
        for ck in candidate_keys:
            #print 'candidate key: ', ck
            #print 'lower_val: ', lower_val
            lower_val_2 = lower_val
            if lower_val != 0:
                if ck not in counts[key][lower]:
                    lower_val_2 = 0
                else:
                    lower_val_2 = counts[key][lower][ck]
            top_k += [ck] * (counts[key][upper][ck] - lower_val_2)
            if len(top_k) >= k:
                break
        top_k = top_k[:k]
        print " ".join(map(str, top_k))

        
line_cost_memo = {}
## Helper function to find cumulative sum
def cumulate(arr):
    sum = 0
    result = []
    for i in range(len(arr)):
        sum += arr[i]
        result.append(sum)
    return result

sum_xs = {}
sum_ys = {}
sum_xs_ys = {}
sum_xs_2 = {}
sum_ys_2 = {}

##Helper fucntion to find range sum
def r_sum(arr, i, j):
    if i == 0:
        lower_val = 0
    else:
        lower_val = arr[i-1]
    return arr[j] - lower_val

#Helper function to find least square lines
def line_cost(xs, ys, key, start, end):
    if (key, start, end) in line_cost_memo:
        return line_cost_memo[(key, start, end)]
    
    if key not in sum_xs:
        sum_xs[key] = cumulate(xs)
        sum_ys[key] = cumulate(ys)
        sum_xs_ys[key] = cumulate([a*b for a,b in zip(xs, ys)])
        sum_xs_2[key] = cumulate([x*x for x in xs])
        sum_ys_2[key] = cumulate([y*y for y in ys])        
        #print sum_xs[key], sum_ys[key], sum_xs_ys[key], sum_xs_2[key], sum_ys_2[key]
        
    n = end - start + 1

    prod_sum = 0
    #for i in range(start, end+1):
    #    prod_sum += xs[i] * ys[i]

    #print 'prod_sum: ', prod_sum
    #print 'range_sum: ',  r_sum(sum_xs_ys[key], start, end)

    #assert r_sum(sum_xs_ys[key], start, end) == prod_sum
    
    a = float(n * r_sum(sum_xs_ys[key], start, end) - r_sum(sum_xs[key], start, end)*r_sum(sum_ys[key], start, end)) / float(n * r_sum(sum_xs_2[key], start, end) - r_sum(sum_xs[key], start, end)**2)

    b = float(r_sum(sum_ys[key], start, end) - a * r_sum(sum_xs[key], start, end)) / n

    #print 'n: %d, a: %f, b: %f' % (n, a, b)

    cost = r_sum(sum_ys_2[key], start, end) + (a*a*r_sum(sum_xs_2[key], start, end)) + n*b*b + \
           2*a*b*r_sum(sum_xs[key], start, end) - 2*a*r_sum(sum_xs_ys[key], start, end) - \
           2*b*r_sum(sum_ys[key], start, end)

    #print 'line_cost: ', cost
        
    line_cost_memo[(key, start, end)] = cost
    return cost

msc_called = [0]


#Helper function to calculate the mininum segment cost between start and end indices
def min_segment_cost(start, end, xs, ys, k, msc_memo, key, recurses_left):
    msc_called[0] += 1
    #print 'min_segment_cost called with', start, end
    if (start, end) in msc_memo:
       # print 'msc_memo', msc_memo        
        return msc_memo[(start, end)]
    if start == end:
        msc_memo[(start, end)] = (0, 1)
        return (0, 1)
    min_cost = (line_cost(xs, ys, key, start, end), 1)
    next_recurses_left = min(recurses_left - 1, int(min_cost[0]/k))
    if next_recurses_left == 0:
        msc_memo[(start, end)] = min_cost
        return min_cost
    #print 'unsegemented cost: ', min_cost
    for i in range(start, end-1):
        #print 'i: ', i
        first_segment_cost = min_segment_cost(start, i, xs, ys, k, msc_memo, key, next_recurses_left)
        second_segment_cost = min_segment_cost(i+1, end, xs, ys, k, msc_memo, key, next_recurses_left)
        segments_cost = first_segment_cost[0] + second_segment_cost[0]
        num_segments = first_segment_cost[1] + second_segment_cost[1]
        if segments_cost + num_segments * k < min_cost[0] + min_cost[1] * k:
            min_cost = (segments_cost, num_segments)
    msc_memo[(start, end)] = min_cost
    #print 'msc_memo', msc_memo
    return min_cost

'''
Delta Query
Assumption: Field value for timestamp is unique
Approach: Cost Matrix is propagated at constant time by storing cumulative sums of x,x*x,y,y*y and x*y for all fields and symbols to calculate the a,b along with regression cost.
Then, Dynamic programming is used to store the between i,j the minimum segment cost for k.
Complexity: 
Time: O(N^2)
Space: O(N*N*F*S) where N-> Number of time stamps F->Number of fields S->Number of symbols
'''
def segment_cost(queries):
    xs, ys = defaultdict(list), defaultdict(list)
    msc_memo = defaultdict(dict)

    for l in lines:
        timestamp = int(l[0])
        symbol = l[1]
        l = l[2:]
        for i in range(0, len(l), 2):
            field, value = l[i], int(l[i+1])
            xs[(symbol, field)].append(timestamp)
            ys[(symbol, field)].append(value)

    for q in queries:
        k = int(q[-1])
        key = (q[1], q[2])
        min_cost = min_segment_cost(0, len(xs[key]) - 1, xs[key], ys[key], k, msc_memo[(key, k)], key, len(xs[key]))
        print int(math.ceil(round((min_cost[0] + min_cost[1] * k),5)))

print "tickfile completed"

called = False

# Runner Segment of code
for line in sys.stdin:
    line = line.split()
    operator = line[0]
    if operator == 'max':
        queries = []
        queries.append(line)
        for l in sys.stdin:
            queries.append(l.split())
        largest_k(queries)
        continue
    elif operator == 'delta':
        queries = []
        queries.append(line)
        for l in sys.stdin:
            queries.append(l.split())
            if len(queries) == 1e3:
                assert False
        segment_cost(queries)
        #print 'msc called: ', msc_called[0]
        continue
            
    elif operator == 'product':
        #print 0
        #continue
        if(line[4]<line[5]):
            key = (line[3],line[4],line[5])
        else: key = (line[3],line[5],line[4])
        if not called:
            product()
            called = True

    elif operator=='sum':
       key = (line[3],line[4])
       if not called:
           my_sum()
           called = True

    if key not in timestamps:
        print 0
        continue
    lower = bisect.bisect_left(timestamps[key], int(line[1])) - 1
    upper = bisect.bisect_right(timestamps[key], int(line[2])) - 1
    if lower < 0:
        lower_val = 0
    else:
        lower_val = sum_store[key][timestamps[key][lower]]
    print sum_store[key][timestamps[key][upper]] - lower_val

    
    
