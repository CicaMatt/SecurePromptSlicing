import os
from werkzeug.utils import secure_filename

def upload_file(file):
    filename = secure_filename(file.filename)
    if not os.path.exists('uploads'):
        os.makedirs('uploads')
    file.save(os.path.join('uploads', filename))