import os
from flask import Flask, request, redirect, url_for
from werkzeug.utils import secure_filename

app = Flask(__name__)

@app.route('/')
def upload_file():
    return '''
    <html>
        <head>
            <title>Upload new File</title>
        </head>
        <body>
            <form action="http://localhost:5000/upload" method="post" enctype="multipart/form-data">
                <input type="file" name="file" /><br/>
                <input type="submit"/>
            </form>
        </body>
    </html>'''

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
            return redirect(url_for('upload_file', filename=filename))
    return 'File uploaded successfully'