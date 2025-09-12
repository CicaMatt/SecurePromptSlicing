import os
import mysql.connector
from flask import Flask, request, send_from_directory

app = Flask(__name__)

# Database configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join('uploads', file.filename)
        file.save(filepath)
        
        # Save filepath to database
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor()
        query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
        cursor.execute(query, (filepath,))
        connection.commit()
        cursor.close()
        connection.close()
        
        return f"File uploaded successfully: {file.filename}", 200
    else:
        return "Invalid file type", 400

@app.route('/download/<filename>')
def download_pdf(filename):
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor(dictionary=True)
    query = "SELECT filepath FROM pdf_files WHERE filepath LIKE %s"
    cursor.execute(query, (f'%{filename}%',))
    result = cursor.fetchone()
    cursor.close()
    connection.close()

    if result:
        return send_from_directory('uploads', filename)
    else:
        return "File not found", 404

if __name__ == '__main__':
    if not os.path.exists('uploads'):
        os.makedirs('uploads')
    app.run(debug=True)