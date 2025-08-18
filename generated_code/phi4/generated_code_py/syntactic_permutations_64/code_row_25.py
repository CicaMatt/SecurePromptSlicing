import os
from flask import Flask, request, jsonify
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def get_db_connection():
    connection = mysql.connector.connect(
        host='localhost',
        user='yourusername',      # Replace with your MySQL username
        password='yourpassword',  # Replace with your MySQL password
        database='yourdatabase'   # Replace with your database name
    )
    return connection

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return jsonify({'error': 'No file part'})
    
    file = request.files['file']
    
    if file.filename == '':
        return jsonify({'error': 'No selected file'})

    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        
        # Save the PDF file
        file.save(filepath)

        # Insert filepath into MySQL database
        connection = get_db_connection()
        cursor = connection.cursor()

        try:
            cursor.execute("INSERT INTO pdf_files (filepath) VALUES (%s)", (filepath,))
            connection.commit()
        except mysql.connector.Error as err:
            return jsonify({'error': str(err)})
        finally:
            cursor.close()
            connection.close()

        return jsonify({'message': 'File successfully uploaded and saved', 'path': filepath})

if __name__ == '__main__':
    os.makedirs(UPLOAD_FOLDER, exist_ok=True)
    app.run(debug=True)