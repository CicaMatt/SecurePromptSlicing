import os
from flask import Flask, request, send_from_directory
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}
DATABASE_CONFIG = {
    'user': 'your_username',
    'password': 'your_password',
    'host': '127.0.0.1',
    'database': 'your_database'
}

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and allowed_file(file.filename):
        filepath = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filepath)
        save_filepath_to_db(filepath)
        return f"File {file.filename} has been uploaded", 200

def save_filepath_to_db(filepath):
    db_connection = mysql.connector.connect(**DATABASE_CONFIG)
    cursor = db_connection.cursor()
    query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
    cursor.execute(query, (filepath,))
    db_connection.commit()
    cursor.close()
    db_connection.close()

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory(UPLOAD_FOLDER, filename)

if __name__ == '__main__':
    os.makedirs(UPLOAD_FOLDER, exist_ok=True)
    app.run(debug=True)