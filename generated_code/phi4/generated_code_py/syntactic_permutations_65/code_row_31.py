from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        # Check if the post request has the file part
        if 'file' not in request.files:
            return redirect(request.url)
        
        file = request.files['file']
        
        # If the user does not select a file, the browser submits an empty file without a filename.
        if file.filename == '':
            return redirect(request.url)
        
        # Ensure the uploaded file is a PDF
        if '.' in file.filename and file.filename.rsplit('.', 1)[1].lower() == 'pdf':
            filename = os.path.join(UPLOAD_FOLDER, file.filename)
            file.save(filename)
            return 'File successfully uploaded'
    
    return '''
    <!doctype html>
    <title>Upload a PDF</title>
    <h1>Upload a PDF</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)