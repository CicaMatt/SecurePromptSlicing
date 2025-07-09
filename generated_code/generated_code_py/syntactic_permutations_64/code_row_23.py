import os
from flask import Flask, request, redirect, url_for
from werkzeug.utils import secure_filename
from sqlalchemy import create_engine

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

def upload_pdf():
    # save file to uploads folder
    def allowed_file(filename):
        return '.' in filename and \
               filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

    @app.route('/upload', methods=['GET', 'POST'])
    def upload_file():
        if request.method == 'POST':
            # check if the post request has the file part
            if 'file' not in request.files:
                flash('No file part')
                return redirect(request.url)
            file = request.files['file']
            if file.filename == '':
                flash('No selected file')
                return redirect(request.url)
            if file and allowed_file(file.filename):
                filename = secure_filename(file.filename)
                file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
                # save filepath to mysql database
                engine = create_engine('mysql://username:password@localhost/database')
                conn = engine.connect()
                conn.execute("INSERT INTO pdfs (filepath) VALUES ('" + os.path.join(app.config['UPLOAD_FOLDER'], filename) + "')")
                return redirect(url_for('uploaded_file',
                                        filename=filename))
        return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)