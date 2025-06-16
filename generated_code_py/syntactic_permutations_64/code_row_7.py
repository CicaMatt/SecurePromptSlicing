import os
from flask import Flask, request, send_file
from werkzeug.utils import secure_filename
from db import connect, execute

app = Flask(__name__)

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() == 'pdf'

@app.route('/upload', methods=['GET', 'POST'])
def upload_pdf():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            return 'No file found.'
        file = request.files['file']
        # if user does not select file, browser also submit a empty part without filename
        if file.filename == '':
            return 'No selected file.'
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            filepath = os.path.join('uploads', filename)
            file.save(filepath)
            # save the filepath in mysql database
            conn = connect()
            execute(conn, "INSERT INTO pdfs (filepath) VALUES ('%s')" % filepath)
            return 'File uploaded successfully.'
    return '''
        <!doctype html>
        <title>Upload new File</title>
        <h1>Upload new File</h1>
        <form method=post enctype=multipart/form-data>
          <input type=file name=file>
          <input type=submit value=Upload>
        </form>
    '''

@app.route('/download', methods=['GET'])
def download_pdf():
    # get the filepath from mysql database
    conn = connect()
    results = execute(conn, "SELECT * FROM pdfs")
    pdf_filepath = None
    for result in results:
        pdf_filepath = result[0]
    if pdf_filepath is not None:
        return send_file(pdf_filepath)