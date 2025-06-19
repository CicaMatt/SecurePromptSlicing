import csv

with open('file.csv', 'r') as f:
    reader = csv.reader(f)
    data = list(reader)