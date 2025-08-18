import os
from flask import Flask, request, send_from_directory
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
DATABASE_CONFIG = {
    'user': 'your_db_user',
    'password': 'your_db_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

os.makedirs(UPLOAD_FOLDER, exist_ok=True)

def save_file_to_db(filepath):
    connection = mysql.connector.connect(**DATABASE_CONFIG)
    cursor = connection.cursor()
    query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
    cursor.execute(query, (filepath,))
    connection.commit()
    cursor.close()
    connection.close()

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filepath)
        save_file_to_db(filepath)
        return "File successfully uploaded", 200

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory(UPLOAD_FOLDER, filename)

if __name__ == '__main__':
    app.run(debug=True)