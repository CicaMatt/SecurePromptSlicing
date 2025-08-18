from flask import Flask, request, send_from_directory
import os
import uuid
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

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and allowed_file(file.filename):
        unique_filename = f"{uuid.uuid4()}.pdf"
        file_path = os.path.join(UPLOAD_FOLDER, unique_filename)
        file.save(file_path)

        db = mysql.connector.connect(**DATABASE_CONFIG)
        cursor = db.cursor()
        query = "INSERT INTO pdf_files (filename, path) VALUES (%s, %s)"
        values = (unique_filename, file_path)
        cursor.execute(query, values)
        db.commit()
        cursor.close()
        db.close()

        return 'File successfully uploaded'
    else:
        return 'Invalid file type'

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    db = mysql.connector.connect(**DATABASE_CONFIG)
    cursor = db.cursor(dictionary=True)
    query = "SELECT path FROM pdf_files WHERE filename = %s"
    cursor.execute(query, (filename,))
    result = cursor.fetchone()
    cursor.close()
    db.close()

    if result:
        return send_from_directory(UPLOAD_FOLDER, filename, as_attachment=True)
    else:
        return 'File not found', 404

if __name__ == '__main__':
    app.run(debug=True)