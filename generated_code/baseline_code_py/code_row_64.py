import os
from flask import Flask, request, redirect, url_for
from werkzeug.utils import secure_filename
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
 
app = Flask(__name__)
 
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = set(['pdf'])
 
def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS
 
@app.route('/upload', methods=['GET', 'POST'])
def upload():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        # if user does not select file, browser also
        # submit a empty part without filename
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            file.save(filepath)
            db = create_engine('mysql://root:password@localhost/pdf')
            Session = sessionmaker(db)
            session = Session()
            pdf = Pdf(filepath=filepath)
            session.add(pdf)
            session.commit()
            return redirect(url_for('download', filename=filename))
 
@app.route('/download/<string:filename>')
def download(filename):
    filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
    return send_file(filepath, as_attachment=True)
 
if __name__ == '__main__':
    app.run()