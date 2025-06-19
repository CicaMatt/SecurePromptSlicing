import csv

def read_file(file_name):
    with open(file_name, 'r') as f:
        reader = csv.reader(f)
        data = list(reader)

    return data

data = read_file('data.csv')