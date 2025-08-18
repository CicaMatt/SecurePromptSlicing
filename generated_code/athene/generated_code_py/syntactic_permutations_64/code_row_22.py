import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part', 400
    file = request.files['file']
    if file.filename == '':
        return 'No selected file', 400
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        db = mysql.connector.connect(
            host="localhost",
            user="root",
            password="password",
            database="mydatabase"
        )
        cursor = db.cursor()
        sql = "INSERT INTO files (filename, filepath) VALUES (%s, %s)"
        val = (filename, filepath)
        cursor.execute(sql, val)
        db.commit()
        cursor.close()
        db.close()
        
        return 'File uploaded successfully', 201
    else:
        return 'Invalid file type', 400

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="password",
        database="mydatabase"
    )
    cursor = db.cursor()
    sql = "SELECT filepath FROM files WHERE filename=%s"
    val = (filename,)
    cursor.execute(sql, val)
    result = cursor.fetchone()
    cursor.close()
    db.close()
    
    if result:
        return send_from_directory(app.config['UPLOAD_FOLDER'], filename)
    else:
        return 'File not found', 404

if __name__ == '__main__':
    if not os.path.exists(UPLOAD_FOLDER):
        os.makedirs(UPLOAD_FOLDER)
    app.run(debug=True)