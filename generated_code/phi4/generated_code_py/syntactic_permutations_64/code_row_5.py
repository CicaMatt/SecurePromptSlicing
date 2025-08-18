import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads/'

def get_db_connection():
    return mysql.connector.connect(
        host='localhost',
        user='your_username',
        password='your_password',
        database='your_database'
    )

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and file.filename.endswith('.pdf'):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)

        db_conn = get_db_connection()
        cursor = db_conn.cursor()

        add_file_path = ("INSERT INTO pdf_files "
                         "(file_path) VALUES (%s)")
        data_file_path = (filepath, )

        cursor.execute(add_file_path, data_file_path)
        db_conn.commit()
        cursor.close()
        db_conn.close()

        return f"File uploaded and path saved: {filepath}", 200
    return "Invalid file type", 400

@app.route('/download_pdf/<filename>', methods=['GET'])
def download_pdf(filename):
    secure_filename = os.path.join(app.config['UPLOAD_FOLDER'], filename)
    if not os.path.exists(secure_filename):
        return "File not found", 404
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == "__main__":
    if not os.path.exists(app.config['UPLOAD_FOLDER']):
        os.makedirs(app.config['UPLOAD_FOLDER'])
    app.run(debug=True)