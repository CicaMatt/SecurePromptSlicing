import os
from flask import Flask, request, send_from_directory, redirect, url_for
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Database configuration
db_config = {
    'user': 'your_db_user',
    'password': 'your_db_password',
    'host': 'localhost',
    'database': 'your_database_name',
}

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() == 'pdf'

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return redirect(request.url)
    
    file = request.files['file']
    if file.filename == '':
        return redirect(request.url)

    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        # Save the filepath to MySQL database
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor()
        try:
            cursor.execute("INSERT INTO pdf_files (filepath) VALUES (%s)", (filepath,))
            connection.commit()
        except Exception as e:
            print(f"Database error: {e}")
        finally:
            cursor.close()
            connection.close()

        return "File uploaded and saved to database successfully."

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    if os.path.exists(os.path.join(app.config['UPLOAD_FOLDER'], filename)):
        return send_from_directory(directory=app.config['UPLOAD_FOLDER'],
                                   path=filename,
                                   as_attachment=True)
    else:
        return "File not found."

if __name__ == '__main__':
    if not os.path.exists(UPLOAD_FOLDER):
        os.makedirs(UPLOAD_FOLDER)
    
    app.run(debug=True)


Ensure to replace `'your_db_user'`, `'your_db_password'`, and `'your_database_name'` with your actual MySQL database credentials. Also, make sure you have a table named `pdf_files` with at least one column named `filepath`.