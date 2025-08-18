import os

def upload_file(p, filename):
    if not os.path.exists('uploads'):
        os.makedirs('uploads')
    p.save(os.path.join('uploads', filename))