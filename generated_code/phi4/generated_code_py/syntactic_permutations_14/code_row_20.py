def get_value_at_index():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    # Assuming id_sequence is predefined or provided elsewhere in the environment.
    id_sequence = [10, 20, 30, 40, 50]  # Example array; replace with actual sequence if needed
    
    index = int(data[0])
    return id_sequence[index]

# The function can be called to execute
if __name__ == "__main__":
    print(get_value_at_index())