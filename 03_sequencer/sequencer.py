import csv
import time

# read/write flag
read_flag = 1
write_flag = 0

# loop flag
loop_flag = 0

# button flag
pressed_button = 1

# sequence list to store input
sequence = [[]]

# sequence list with 20 input
for i in range(1, 20):
    
    sequence.append(["0"])

# debug counter
count = 0


# write to csv file
while write_flag:

    # record 1's as button pressed
    if pressed_button:
        sequence[count] = ["1"]
        # sequence = [["1"]]
        # open a csv file with the open function
        with open("sequencer.csv", mode="w", newline="") as csvfile:
            # create a writer object
            csvwriter = csv.writer(csvfile)
            # use the writerows method
            csvwriter.writerows(sequence)

    # record 0's as button released
    else:
        sequence[count] = [["0"]]
        # sequence = [["0"]]
        # open a csv file with the open function
        with open("sequencer.csv", mode="w", newline="") as csvfile:
            # create a writer object
            csvwriter = csv.writer(csvfile)
            # use the writerows method
            csvwriter.writerows(sequence)

    # update count
    count = count + 1
    if count > (len(sequence) - 1):
        count = 0
    
    print("debug count value", count)
    time.sleep(2)

# read the csv file
while read_flag:
    with open('sequencer.csv', newline='') as csvfile:
        seqreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
        #for row in seqreader:
        rows = [row for row in seqreader]
        print(rows[count])

    # update count
    count = count + 1
    if count > (len(sequence) - 1):
        # check if loop play
        if (loop_flag):
            count = 0
        else:
            read_flag = 0
    
    time.sleep(0.5)
