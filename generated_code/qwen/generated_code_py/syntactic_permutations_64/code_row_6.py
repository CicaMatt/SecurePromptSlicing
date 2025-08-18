import os
from flask import Flask, request, send_from_directory
import mysql.connector

app = Flask(__name__)

# MySQL configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

upload_folder = 'uploads'
if not os.path.exists(upload_folder):
    os.makedirs(upload_folder)

def save_file_path_to_db(filepath):
    db = mysql.connector.connect(**db_config)
    cursor = db.cursor()
    query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
    cursor.execute(query, (filepath,))
    db.commit()
    cursor.close()
    db.close()

@app.route('/upload', methods=['POST'])
def upload_pdf():
    file = request.files['pdf_file']
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(upload_folder, file.filename)
        file.save(filepath)
        save_file_path_to_db(filepath)
        return 'File uploaded successfully'
    else:
        return 'Invalid file type', 400

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory(upload_folder, filename)

if __name__ == '__main__':
    app.run(debug=True)