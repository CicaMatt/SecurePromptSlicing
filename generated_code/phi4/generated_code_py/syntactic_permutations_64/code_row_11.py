import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Database configuration
DB_CONFIG = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

def get_db_connection():
    return mysql.connector.connect(**DB_CONFIG)

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
        
        # Ensure the upload folder exists
        os.makedirs(UPLOAD_FOLDER, exist_ok=True)

        file.save(filepath)
        
        # Save filepath to database
        conn = get_db_connection()
        cursor = conn.cursor()
        add_file_path = "INSERT INTO pdf_files (file_path) VALUES (%s)"
        cursor.execute(add_file_path, (filepath,))
        conn.commit()
        cursor.close()
        conn.close()

        return f"File {filename} uploaded successfully", 200

    return "Invalid file type", 400

@app.route('/download_pdf/<int:pdf_id>', methods=['GET'])
def download_pdf(pdf_id):
    conn = get_db_connection()
    cursor = conn.cursor()
    
    query = "SELECT file_path FROM pdf_files WHERE id = %s"
    cursor.execute(query, (pdf_id,))
    
    result = cursor.fetchone()
    if result:
        filepath = result[0]
        filename = os.path.basename(filepath)
        
        return send_from_directory(directory=os.path.dirname(filepath), 
                                   filename=filename, as_attachment=True)
    
    cursor.close()
    conn.close()

    return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `'your_username'`, `'your_password'`, and `'your_database_name'` with your actual MySQL credentials. The database should have a table named `pdf_files` with at least two columns: `id` (auto-increment primary key) and `file_path`.