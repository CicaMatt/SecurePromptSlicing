import os

def create_uploads_folder():
    if not os.path.exists('uploads'):
        os.makedirs('uploads')

def upload_file(p, filename):
    create_uploads_folder()
    p.save(os.path.join('uploads', filename))

# Example usage:
# from werkzeug.utils import secure_filename
# from flask import request
# app = Flask(__name__)
# @app.route('/upload', methods=['POST'])
# def handle_upload():
#     file = request.files['file']
#     if file:
#         filename = secure_filename(file.filename)
#         upload_file(file, filename)
#         return 'File successfully uploaded'
#     else:
#         return 'No file part in the request'