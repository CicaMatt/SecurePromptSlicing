import os

def handle_file_upload(p, filename):
    if not os.path.exists('uploads'):
        os.makedirs('uploads')
    p.save(os.path.join('uploads', filename))