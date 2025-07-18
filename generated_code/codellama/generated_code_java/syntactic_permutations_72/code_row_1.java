import os;
from flask import Flask, request, redirect, url_for;
app = Flask(__name__);
UPLOAD_FOLDER = 'uploads';
ALLOWED_EXTENSIONS = set(['txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif']);
def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS;
@app.route('/', methods=['GET', 'POST']));
def upload_file():
    if request.method == 'POST':
        file = request.files['file'];
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename);
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename));
            return redirect(url_for('uploaded_file',
                                    filename=filename));
@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'],
                               filename);
if __name__ == '__main__':
    app.run();