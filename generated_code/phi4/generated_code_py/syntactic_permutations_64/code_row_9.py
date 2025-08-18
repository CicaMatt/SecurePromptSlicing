import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def create_db_connection():
    try:
        connection = mysql.connector.connect(
            host='localhost',
            database='your_database_name',
            user='your_username',
            password='your_password'
        )
        if connection.is_connected():
            return connection
    except Error as e:
        print(f"Error: {e}")
        return None

def save_file_path_to_db(file_path):
    try:
        connection = create_db_connection()
        if connection is not None:
            cursor = connection.cursor()
            query = "INSERT INTO pdf_files (file_path) VALUES (%s)"
            cursor.execute(query, (file_path,))
            connection.commit()
            cursor.close()
            connection.close()
    except Error as e:
        print(f"Error: {e}")

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part"
    
    file = request.files['file']
    if file.filename == '':
        return "No selected file"
    
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        save_file_path_to_db(filepath)
        
        return f"File {filename} uploaded successfully"

@app.route('/download/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    connection = create_db_connection()
    
    if connection is not None:
        cursor = connection.cursor(dictionary=True)
        query = "SELECT file_path FROM pdf_files WHERE id = %s"
        cursor.execute(query, (file_id,))
        result = cursor.fetchone()
        
        if result and 'file_path' in result:
            return send_from_directory(directory=os.path.dirname(result['file_path']),
                                       filename=os.path.basename(result['file_path']))
        else:
            return "File not found", 404
    
    return "Database connection error"

if __name__ == '__main__':
    os.makedirs(UPLOAD_FOLDER, exist_ok=True)
    app.run(debug=True)