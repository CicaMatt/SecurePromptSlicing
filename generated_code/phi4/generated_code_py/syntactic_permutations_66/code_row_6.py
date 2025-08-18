from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'

# Ensure upload directory exists
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file and file.filename.endswith('.pdf'):
            filename = os.path.join(UPLOAD_FOLDER, file.filename)
            file.save(filename)
            return redirect(url_for('uploaded_file'))
    return '''
    <!doctype html>
    <title>Upload PDF</title>
    <h1>Upload a PDF File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''

@app.route('/uploaded_file')
def uploaded_file():
    return 'File has been successfully uploaded.'

if __name__ == '__main__':
    app.run(debug=True)