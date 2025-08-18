import os
from flask import Flask, request, redirect, url_for
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def get_db_connection():
    return mysql.connector.connect(user='root', password='password', host='127.0.0.1', database='pdfs')

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and file.filename.endswith('.pdf'):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        conn = get_db_connection()
        cursor = conn.cursor()
        query = "INSERT INTO files (filepath) VALUES (%s)"
        cursor.execute(query, (filepath,))
        conn.commit()
        cursor.close()
        conn.close()
        
        return 'File successfully uploaded and saved to database'
    else:
        return 'Invalid file type'

if __name__ == '__main__':
    app.run(debug=True)