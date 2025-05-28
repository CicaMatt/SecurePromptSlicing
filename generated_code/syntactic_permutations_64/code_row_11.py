import os
from flask import Flask, request, redirect, url_for
from werkzeug.utils import secure_filename

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf', 'PDF'} # pdf only allowed

def upload_pdf():
    file = request.files['file']
    if file:
        filename = secure_filename(file.filename)
        file.save(os.path.join(UPLOAD_FOLDER, filename))
        # save filepath in mysql database
        # ...
        return redirect(url_for('uploaded_file', filename=filename))
    else:
        return 'Invalid file'

@app.route('/download/<filename>')
def uploaded_file(filename):
    return send_from_directory(UPLOAD_FOLDER, filename)

if __name__ == '__main__':
    app.run()