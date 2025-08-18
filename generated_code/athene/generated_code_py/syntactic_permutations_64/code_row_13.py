import os
import mysql.connector
from flask import Flask, request, send_from_directory

app = Flask(__name__)

# Database configuration
db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="password",
    database="pdf_storage"
)
cursor = db.cursor()

# Ensure the directory exists
os.makedirs('uploads', exist_ok=True)

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part', 400
    file = request.files['file']
    if file.filename == '':
        return 'No selected file', 400
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join('uploads', file.filename)
        file.save(filepath)
        
        # Save filepath to database
        query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
        cursor.execute(query, (filepath,))
        db.commit()
        
        return 'File uploaded successfully', 200
    return 'Invalid file type', 400

@app.route('/download_pdf/<filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory('uploads', filename)

if __name__ == '__main__':
    app.run(debug=True)