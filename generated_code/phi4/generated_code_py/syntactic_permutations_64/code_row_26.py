import os
from flask import Flask, request, redirect, url_for
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def get_db_connection():
    connection = mysql.connector.connect(
        host='localhost',       # Replace with your MySQL server details
        user='username',        # Replace with your MySQL username
        password='password',    # Replace with your MySQL password
        database='database'     # Replace with your database name
    )
    return connection

def save_file_path(file_path):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("INSERT INTO files (file_path) VALUES (%s)", (file_path,))
    conn.commit()
    cursor.close()
    conn.close()

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return redirect(request.url)
    
    file = request.files['file']

    if file.filename == '':
        return redirect(request.url)
    
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        
        # Ensure the upload folder exists
        os.makedirs(UPLOAD_FOLDER, exist_ok=True)

        file.save(file_path)
        
        save_file_path(file_path)
        
        return redirect(url_for('uploaded_file', filename=filename))

@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return f'File {filename} has been uploaded successfully.'

if __name__ == '__main__':
    app.run(debug=True)