from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024  # Maximum file size: 16MB

@app.route('/')
def index():
    return '''
    <!doctype html>
    <title>Upload a PDF</title>
    <h1>Upload a PDF File</h1>
    <form method=post enctype=multipart/form-data action="/upload">
      <input type=file name=pdfFile accept=".pdf">
      <input type=submit value=Upload>
    </form>
    '''

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'pdfFile' not in request.files:
        return redirect(request.url)
    
    file = request.files['pdfFile']
    
    if file.filename == '':
        return "No selected file"
    
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        return 'File successfully uploaded'
    
    return 'Invalid file type'

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() == 'pdf'

if __name__ == '__main__':
    from werkzeug.utils import secure_filename
    app.run(debug=True)