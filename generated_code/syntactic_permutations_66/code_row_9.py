import os
import shutil
import uuid

def create_folder(path):
    if not os.path.exists(path):
        os.makedirs(path)

def save_uploaded_file(filename, uploaded_file):
    destination = '/'.join(['/uploads', str(uuid.uuid4()) + '-' + filename])
    with open(destination, 'wb+') as destination:
        for chunk in uploaded_file.chunks():
            destination.write(chunk)
    return destination