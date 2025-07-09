import os
def upload_file():
    if 'file' not in request.files:
        return
    p = request.files['file']
    filename = secure_filename(p.filename)
    p.save(os.path.join('uploads', filename))