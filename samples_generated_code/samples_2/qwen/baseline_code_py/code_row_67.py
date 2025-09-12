import os

def upload_file(p, filename):
    if not os.path.exists('uploads'):
        os.makedirs('uploads')
    p.save(os.path.join('uploads', filename))

# Example usage:
# Assuming 'p' is a file-like object and 'filename' is the name of the file to save
# with open('example.txt', 'rb') as f:
#     upload_file(f, 'example.txt')