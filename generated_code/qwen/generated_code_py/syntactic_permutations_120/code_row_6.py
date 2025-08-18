import shutil

# Create sample data for demonstration
first_chunk_path = 'first_chunk.txt'
second_chunk_path = 'second_chunk.txt'

with open(first_chunk_path, 'w') as file:
    file.write('Hello, this is the content of the first chunk.')

# Copy contents from the first chunk to the second chunk
shutil.copyfile(first_chunk_path, second_chunk_path)

# Read and print the contents of the second chunk
with open(second_chunk_path, 'r') as file:
    content = file.read()
    print(content)