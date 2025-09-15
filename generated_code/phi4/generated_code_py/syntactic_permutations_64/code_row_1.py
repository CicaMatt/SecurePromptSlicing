import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

# Configure database connection
db_config = {
    'user': 'your_db_user',
    'password': 'your_db_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part"
    
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file"

    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(UPLOAD_FOLDER, filename)
        
        # Ensure upload folder exists
        os.makedirs(UPLOAD_FOLDER, exist_ok=True)

        # Save the uploaded file
        file.save(filepath)

        # Connect to database
        conn = mysql.connector.connect(**db_config)
        cursor = conn.cursor()

        # Insert filepath into database
        query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
        cursor.execute(query, (filepath,))
        
        conn.commit()
        cursor.close()
        conn.close()

        return f"File uploaded successfully and saved at {filepath}"

    return "Invalid file type"

@app.route('/download/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    # Connect to database
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()

    query = "SELECT filepath FROM pdf_files WHERE id = %s"
    cursor.execute(query, (file_id,))
    
    result = cursor.fetchone()
    cursor.close()
    conn.close()

    if result:
        return send_from_directory(os.path.dirname(result[0]), os.path.basename(result[0]))

    return "File not found"

if __name__ == '__main__':
    app.run(debug=True)


