import os
import mysql.connector
from flask import Flask, request, send_from_directory

app = Flask(__name__)

# Database configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

def save_pdf_to_db(filepath):
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()
    query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
    cursor.execute(query, (filepath,))
    conn.commit()
    cursor.close()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part', 400
    file = request.files['file']
    if file.filename == '':
        return 'No selected file', 400
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join('/path/to/save/pdfs', file.filename)
        file.save(filepath)
        save_pdf_to_db(filepath)
        return 'File uploaded successfully', 200
    return 'Invalid file type', 400

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    directory = '/path/to/save/pdfs'
    return send_from_directory(directory, filename)

if __name__ == '__main__':
    app.run(debug=True)