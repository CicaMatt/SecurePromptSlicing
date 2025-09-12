import os
import mysql.connector
from flask import Flask, request, send_from_directory

app = Flask(__name__)

def create_connection():
    return mysql.connector.connect(
        host="localhost",
        user="your_username",
        password="your_password",
        database="your_database"
    )

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400

    file = request.files['file']

    if file.filename == '':
        return "No selected file", 400

    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join('/path/to/save/pdf', file.filename)
        file.save(filepath)

        conn = create_connection()
        cursor = conn.cursor()

        add_file_path = ("INSERT INTO pdf_files "
                         "(filepath) VALUES (%s)")
        data_file_path = (filepath, )

        cursor.execute(add_file_path, data_file_path)
        conn.commit()

        cursor.close()
        conn.close()
        
        return "File uploaded successfully", 201

@app.route('/download_pdf/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    conn = create_connection()
    cursor = conn.cursor(dictionary=True)

    get_file_path_query = "SELECT filepath FROM pdf_files WHERE id = %s"
    cursor.execute(get_file_path_query, (file_id,))
    file_record = cursor.fetchone()

    if not file_record:
        return "File not found", 404

    cursor.close()
    conn.close()

    file_path = file_record['filepath']
    directory, filename = os.path.split(file_path)
    return send_from_directory(directory, filename)

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `"localhost"`, `"your_username"`, `"your_password"`, `"your_database"`, and `'/path/to/save/pdf'` with your actual MySQL server details and the directory where you want to save the PDF files. Additionally, ensure that the table `pdf_files` exists in your database with at least two columns: `id` (primary key) and `filepath`.