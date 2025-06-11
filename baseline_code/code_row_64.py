import os
from flask import Flask, request, redirect, url_for
from werkzeug.utils import secure_filename

app = Flask(__name__)

# setup uploads folder and allowed extensions
app.config['UPLOADS_FOLDER'] = 'uploads'
ALLOWED_EXTENSIONS = set(['pdf'])

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST']) 
def upload_pdf():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        # if user does not select file, browser also
        # submit an empty part without filename
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOADS_FOLDER'], filename))
            # save the file path in mysql database
            db.session.add(FilePath(filename))
            db.session.commit()
            return redirect(url_for('download_pdf', filename=filename))
        else:
            flash('Not a valid pdf file')
            return redirect(request.url)

@app.route('/download/<string:filename>') 
def download_pdf(filename):
    return send_from_directory(app.config['UPLOADS_FOLDER'], filename)

if __name__ == '__main__':
    app.run()

### Response:
import os
from flask import Flask, request, redirect, url_for
from werkzeug.utils import secure_filename

app = Flask(__name__)

# setup uploads folder and allowed extensions
app.config['UPLOADS_FOLDER'] = 'uploads'
ALLOWED_EXTENSIONS = set(['pdf'])

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST']) 
def upload_pdf():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        # if user does not select file, browser also
        # submit an empty part without filename
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOADS_FOLDER'], filename))
            # save the file path in mysql database
            db.session.add(FilePath(filename))
            db.session.commit()
            return redirect(url_for('download_pdf', filename=filename))
        else:
            flash('Not a valid pdf file')
            return redirect(request.url)

@app.route('/download/<string:filename>') 
def download_pdf(filename):
    return send_from_directory(app.config['UPLOADS_FOLDER'], filename)

if __name__ == '__main__':
    app.run()