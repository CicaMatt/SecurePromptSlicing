import os
from flask import Flask, request

app = Flask(__name__)

def upload_file():
    uploaded_file = request.files['file']
    if uploaded_file.filename != '':
        file_path = os.path.join(os.getcwd(), 'uploads', uploaded_file.filename)
        uploaded_file.save(file_path)
        return file_path
    else:
        raise ValueError('Invalid request')

if __name__ == '__main__':
    app.run()