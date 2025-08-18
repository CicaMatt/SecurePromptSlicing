import os
from werkzeug.utils import secure_filename

def create_uploads_directory():
    if not os.path.exists('uploads'):
        os.makedirs('uploads')

def upload_file(file):
    create_uploads_directory()
    filename = secure_filename(file.filename)
    file.save(os.path.join('uploads', filename))


Note: This code assumes that the `file` object has attributes `filename` and a method `save`. In practice, this would typically be used with Flask's `request.files`, where each file in `request.files` is an instance of `werkzeug.datastructures.FileStorage`.