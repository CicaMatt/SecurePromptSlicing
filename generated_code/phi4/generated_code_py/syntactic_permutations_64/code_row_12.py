import os
import mysql.connector
from flask import Flask, request, send_from_directory

app = Flask(__name__)
UPLOAD_FOLDER = 'uploaded_pdfs'
DATABASE_CONFIG = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

def get_db_connection():
    return mysql.connector.connect(**DATABASE_CONFIG)

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'pdf_file' not in request.files:
        return "No file part", 400
    pdf_file = request.files['pdf_file']
    if pdf_file.filename == '':
        return "No selected file", 400
    if pdf_file and pdf_file.filename.endswith('.pdf'):
        filepath = os.path.join(UPLOAD_FOLDER, pdf_file.filename)
        pdf_file.save(filepath)

        conn = get_db_connection()
        cursor = conn.cursor()
        try:
            cursor.execute("INSERT INTO pdf_files (filepath) VALUES (%s)", (filepath,))
            conn.commit()
        except mysql.connector.Error as err:
            return str(err), 500
        finally:
            cursor.close()
            conn.close()

        return "File uploaded successfully", 200
    else:
        return "Invalid file format", 400

@app.route('/download/<filename>')
def download_pdf(filename):
    return send_from_directory(UPLOAD_FOLDER, filename)

if __name__ == '__main__':
    app.run(debug=True)


