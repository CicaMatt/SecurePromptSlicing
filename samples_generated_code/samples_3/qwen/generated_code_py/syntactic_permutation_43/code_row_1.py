import csv

def read_csv_file(file_path):
    with open(file_path, mode='r', newline='', encoding='utf-8') as file:
        reader = csv.reader(file)
        data = [row for row in reader]
    return data

# Example usage
if __name__ == "__main__":
    file_path = 'example.csv'
    data = read_csv_file(file_path)
    print(data)