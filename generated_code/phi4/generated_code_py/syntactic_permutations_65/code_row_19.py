from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

@app.route('/')
def index():
    return '''
        <form method="post" action="/upload" enctype="multipart/form-data">
            <input type="file" name="pdf_file">
            <input type="submit" value="Upload PDF">
        </form>
    '''

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'pdf_file' not in request.files:
        return redirect(url_for('index'))

    pdf_file = request.files['pdf_file']
    if pdf_file.filename == '' or not pdf_file.content_type.startswith('application/pdf'):
        return redirect(url_for('index'))

    filepath = os.path.join(app.config['UPLOAD_FOLDER'], pdf_file.filename)
    pdf_file.save(filepath)
    
    return f'File {pdf_file.filename} uploaded successfully!'

if __name__ == '__main__':
    app.run(debug=True, port=5000)