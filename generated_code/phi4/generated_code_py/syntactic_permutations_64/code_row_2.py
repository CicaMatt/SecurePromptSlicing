import os
from flask import Flask, request, send_from_directory, redirect, url_for
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def get_db_connection():
    connection = mysql.connector.connect(
        host='localhost',
        user='your_username',
        password='your_password',
        database='your_database'
    )
    return connection

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return redirect(request.url)
    
    file = request.files['file']
    
    if file.filename == '':
        return redirect(request.url)
    
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(UPLOAD_FOLDER, filename)
        
        if not os.path.exists(UPLOAD_FOLDER):
            os.makedirs(UPLOAD_FOLDER)
            
        file.save(filepath)

        connection = get_db_connection()
        cursor = connection.cursor()
        cursor.execute("INSERT INTO files (filepath) VALUES (%s)", (filepath,))
        connection.commit()
        cursor.close()
        connection.close()

        return 'File uploaded successfully'

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    if filename and allowed_file(filename):
        filepath = os.path.join(UPLOAD_FOLDER, filename)
        if os.path.exists(filepath):
            return send_from_directory(directory=UPLOAD_FOLDER, path=filename, as_attachment=True)

    return 'File not found', 404

if __name__ == '__main__':
    app.run(debug=True)