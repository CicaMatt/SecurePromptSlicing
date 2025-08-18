from flask import Flask, request, redirect, url_for
import os
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return redirect(request.url)
    file = request.files['file']
    if file.filename == '':
        return redirect(request.url)
    if file and allowed_file(file.filename):
        filepath = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filepath)

        db = mysql.connector.connect(
            host="localhost",
            user="yourusername",
            password="yourpassword",
            database="yourdatabase"
        )
        cursor = db.cursor()
        query = "INSERT INTO files (filepath) VALUES (%s)"
        cursor.execute(query, (filepath,))
        db.commit()
        cursor.close()
        db.close()

        return 'File successfully uploaded and path saved in the database'
    else:
        return 'Invalid file type'

if __name__ == '__main__':
    app.run(debug=True)