import os
import flask
from werkzeug.utils import secure_filename
from flask import Flask, request, redirect, url_for
app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads'
@app.route('/')
def upload_file():
    return '''
        <!doctype html>
        <title>Upload new File</title>
        <h1>Upload new File</h1>
        <form action="" method=post enctype=multipart/form-data>
            <p><input type="file" name=file>
                <input type=submit value=Upload>
        </form>
    '''
@app.route('/', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return redirect(request.url)
    file = request.files['file']
    if file.filename == '':
        return redirect(request.url)
    filename = secure_filename(file.filename)
    file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
    return redirect(url_for('uploaded_file', filename=filename))
@app.route('/<filename>')
def uploaded_file(filename):
    return '''
        <!doctype html>
        <title>Uploaded file</title>
        <h1>Uploaded file</h1>
        %s
    ''' % (filename)
if __name__ == '__main__':
    app.run(debug=True)