from flask import Flask, request, send_from_directory
import os
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}
DATABASE_CONFIG = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and allowed_file(file.filename):
        filename = file.filename
        file.save(os.path.join(UPLOAD_FOLDER, filename))
        save_to_database(filename)
        return f'File {filename} successfully uploaded'
    else:
        return 'Invalid file type'

def save_to_database(filename):
    conn = mysql.connector.connect(**DATABASE_CONFIG)
    cursor = conn.cursor()
    query = "INSERT INTO pdf_files (filename) VALUES (%s)"
    cursor.execute(query, (filename,))
    conn.commit()
    cursor.close()
    conn.close()

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory(UPLOAD_FOLDER, filename)

if __name__ == '__main__':
    app.run(debug=True)