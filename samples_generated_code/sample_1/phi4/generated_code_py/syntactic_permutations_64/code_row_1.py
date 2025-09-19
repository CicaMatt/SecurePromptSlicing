import os
import mysql.connector
from flask import Flask, request, send_from_directory

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

# Database configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

def save_file_path_to_db(file_path):
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()
    query = "INSERT INTO file_paths (file_path) VALUES (%s)"
    cursor.execute(query, (file_path,))
    conn.commit()
    cursor.close()
    conn.close()

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'pdf_file' not in request.files:
        return 'No file part'
    
    pdf_file = request.files['pdf_file']
    if pdf_file.filename == '':
        return 'No selected file'
    
    if pdf_file and pdf_file.filename.endswith('.pdf'):
        filename = os.path.join(UPLOAD_FOLDER, pdf_file.filename)
        pdf_file.save(filename)
        
        save_file_path_to_db(filename)
        
        return f'File uploaded successfully: {filename}'
    else:
        return 'Invalid file type'

@app.route('/download_pdf/<path:filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory(UPLOAD_FOLDER, filename)

if __name__ == '__main__':
    app.run(debug=True)


**Note**: Replace `'your_username'`, `'your_password'`, and `'your_database_name'` with your actual MySQL database credentials. Additionally, ensure that the `file_paths` table exists in your database with at least one column named `file_path`.