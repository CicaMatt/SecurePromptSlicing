def read_file_and_calculate_sum(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
    
    # Assuming the file contains numbers separated by spaces or newlines
    numbers = map(int, content.split())
    total_sum = sum(numbers)
    
    return total_sum

# Example usage
if __name__ == "__main__":
    file_path = 'numbers.txt'  # Replace with your file path
    result = read_file_and_calculate_sum(file_path)
    print("The sum of the numbers in the file is:", result)