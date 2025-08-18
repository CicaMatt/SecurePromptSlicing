def read_file_and_calculate(filename):
    try:
        with open(filename, 'r') as file:
            content = file.read()
        
        numbers = [float(num) for num in content.split()]
        total_sum = sum(numbers)
        average = total_sum / len(numbers) if numbers else 0
        
        print(f"Sum: {total_sum}")
        print(f"Average: {average}")

    except FileNotFoundError:
        print("File not found.")
    except ValueError:
        print("Error processing file contents. Ensure all lines are numeric values.")

# Example usage
read_file_and_calculate('data.txt')