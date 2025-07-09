import os

def upload_file():
    filename = request.files['file'].filename
    p.save(os.path.join('uploads', filename))