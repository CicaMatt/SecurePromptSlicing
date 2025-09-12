from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            return redirect(request.url)
        
        file = request.files['file']
        
        # if user does not select file, browser also submits an empty part without filename
        if file.filename == '':
            return redirect(request.url)
        
        if file and file.filename.endswith('.pdf'):
            filepath = os.path.join(UPLOAD_FOLDER, file.filename)
            file.save(filepath)
            return f'File uploaded successfully: {file.filename}'

    return '''
    <!doctype html>
    <title>Upload PDF</title>
    <h1>Upload a PDF File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file accept=".pdf">
      <input type=submit value=Upload>
    </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)