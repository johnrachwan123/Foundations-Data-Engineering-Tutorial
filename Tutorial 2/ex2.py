import csv
with open('gmane.linux.kernel', encoding="latin-1") as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quoting=csv.QUOTE_NONE)
    max = 0
    result = 0
    b=0
    for row in spamreader:
        if row and row[0]=='Archived-At:':
            b=1
        elif b==1 and row and row[0] == "Path:":
            if(max-3>result):
                result=max-3
            b=0
            max=0
        elif b==1:
            max+=1
print(result)