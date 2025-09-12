import os
from werkzeug.utils import secure_filename

def upload_file(file):
    filename = secure_filename(file.filename)
    file_path = os.path.join('uploads', filename)
    file.save(file_path)