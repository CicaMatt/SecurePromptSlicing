import os
from werkzeug.utils import secure_filename

def create_uploads_folder():
    if not os.path.exists('uploads'):
        os.makedirs('uploads')

def upload_file(file):
    create_uploads_folder()
    filename = secure_filename(file.filename)
    filepath = os.path.join('uploads', filename)
    file.save(filepath)
    return filepath