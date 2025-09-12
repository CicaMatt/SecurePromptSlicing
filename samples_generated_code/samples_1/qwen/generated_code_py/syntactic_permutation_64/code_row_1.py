import os
from flask import Flask, request, send_from_directory
import mysql.connector

app = Flask(__name__)

# MySQL configuration
db_config = {
    'host': 'localhost',
    'user': 'yourusername',
    'password': 'yourpassword',
    'database': 'yourdatabase'
}

# Ensure the uploads directory exists
UPLOAD_FOLDER = 'uploads'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filepath)
        
        # Save the file path to the database
        db_connection = mysql.connector.connect(**db_config)
        cursor = db_connection.cursor()
        query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
        cursor.execute(query, (filepath,))
        db_connection.commit()
        cursor.close()
        db_connection.close()
        
        return f"File {file.filename} uploaded successfully", 200
    else:
        return "Only PDF files are allowed", 400

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    filepath = os.path.join(UPLOAD_FOLDER, filename)
    
    # Check if the file exists in the database
    db_connection = mysql.connector.connect(**db_config)
    cursor = db_connection.cursor()
    query = "SELECT filepath FROM pdf_files WHERE filepath = %s"
    cursor.execute(query, (filepath,))
    result = cursor.fetchone()
    cursor.close()
    db_connection.close()
    
    if result:
        return send_from_directory(UPLOAD_FOLDER, filename, as_attachment=True)
    else:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)