fin = open("eurovision.csv", "r") #input file
fout = open("results.csv", "w") #output file

count = fin.readline() #reading lines count
countries = []
matrix = []
column = []

#rate function
def rate(col):
    col.sort(reverse = True)
    countries[col[0][1]][1] = countries[col[0][1]][1] + 12
    countries[col[1][1]][1] = countries[col[1][1]][1] + 10
    for i in range(2,10):
        countries[col[i][1]][1] = countries[col[i][1]][1] + (10 - i)

#output results to file
def output():
    countries.sort(key=lambda x: x[1])
    countries.reverse()
    for i in range(10):
        fout.write(str(countries[i][0]) + ',' + str(countries[i][1]) + '\n')

#creating arrays of countries and matrix
for line in range(int(count)):
    line = fin.readline()
    buff = line.rstrip().split(',')
    countries.append([buff[0], 0])
    del(buff[0])
    matrix.append(buff)

#going by columns and adding points
for j in range(int(count)):
    for i in range(int(count)):
        buff = int(matrix[i][j])
        column.append([buff, i])
    rate(column)
    column = []

output()
fin.close()
fout.close()
