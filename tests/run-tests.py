import subprocess
import os

os.chdir('../src')
#makes bin/main{00-02} with -O0 -O1 -O2
make_cmd = ('gcc -ggdb -Wall -Wextra -lm -O2 -o bin/main_test main_test.c hilbert.S' +
            ' hilbert.c file_helper.c arg_parse.c')

subprocess.run(make_cmd.split())
#programs = ["./bin/main00", "./bin/main01", "./bin/main02", "./bin/main"]
program_ass = ['./bin/main_test']
program_c = ['./bin/main_test', '-c']

avg_time_ass = []
avg_time_c = []

extra_loops = 7

degree_start = 7
degree_end = 14

def run_tests(avg_time, extra_loops, prog):
        print('running : {}'.format(prog[0]))
        for j in range(degree_start, degree_end):
            avg = 0.0
            flags =  '-d' + str(j)
            #print(flags)
            print('running for degree: {}'.format(j))
            # add the new flag to list
            prog.append(flags)
            # runing some more times to have an average
            for k in range(0, extra_loops):
                t = float(subprocess.check_output(prog))
                avg = avg + t
            avg = avg / extra_loops
            print('avg {}'.format(avg))
            avg_time.append(avg)
            avg = 0
            # delete last elemnt of list (old degree)
            prog = prog[:-1]
            #print('AVERAGE for degree {}: {}',format(j, str(avg)))

run_tests(avg_time_c, extra_loops, program_c)
run_tests(avg_time_ass, extra_loops, program_ass)

os.chdir('../tests')
f = open('c-vs-ass-output', 'w+')
for j in range(0, len(avg_time_c)):
    # to start at the same degree
    line = str(j + degree_start) + ' '
    line += str(avg_time_c[j]) + ' '
    line += str(avg_time_ass[j])
    line += '\n'
    f.write(line)
