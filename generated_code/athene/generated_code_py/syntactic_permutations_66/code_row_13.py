from flask import Flask, request, redirect, url_for, flash
from werkzeug.utils import secure_filename
import os

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = '/path/to/the/uploads'
app.secret_key = 'some_secret'

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        flash('No file part')
        return redirect(request.url)
    file = request.files['file']
    if file.filename == '':
        flash('No selected file')
        return redirect(request.url)
    if file and file.filename.endswith('.pdf'):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        return f"File {filename} has been uploaded successfully."
    else:
        flash('Allowed file types are pdf')
        return redirect(request.url)

if __name__ == '__main__':
    app.run(debug=True)