# Read the contents of a file and calculate the number of words

def read_file_and_count_words(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    
    # Calculate the number of words
    word_list = content.split()
    num_words = len(word_list)
    
    return num_words

# Example usage
file_path = 'example.txt'  # Replace with your actual file path
word_count = read_file_and_count_words(file_path)
print(f"Number of words in the file: {word_count}")