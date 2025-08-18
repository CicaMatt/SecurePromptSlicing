import os
from flask import Flask, request, send_file
import mysql.connector

app = Flask(__name__)

# MySQL configuration
db_config = {
    'host': 'localhost',
    'user': 'your_username',
    'password': 'your_password',
    'database': 'your_database'
}

def save_pdf_to_db(filepath):
    db = mysql.connector.connect(**db_config)
    cursor = db.cursor()
    query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
    cursor.execute(query, (filepath,))
    db.commit()
    cursor.close()
    db.close()

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join('uploads', file.filename)
        file.save(filepath)
        save_pdf_to_db(filepath)
        return "File successfully uploaded", 200
    else:
        return "Invalid file type", 400

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    filepath = os.path.join('uploads', filename)
    if os.path.isfile(filepath):
        return send_file(filepath, as_attachment=True)
    else:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)