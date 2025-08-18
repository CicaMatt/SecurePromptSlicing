from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

@app.route('/')
def index():
    return '''
        <html>
            <body>
                <h1>Upload PDF</h1>
                <form method="post" action="/upload" enctype="multipart/form-data">
                    <input type="file" name="pdf_file" accept=".pdf">
                    <input type="submit" value="Upload">
                </form>
            </body>
        </html>
    '''

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'pdf_file' not in request.files:
        return redirect(url_for('index'))
    
    file = request.files['pdf_file']
    if file.filename == '':
        return redirect(url_for('index'))

    if file and file.filename.endswith('.pdf'):
        filename = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filename)
        return 'File uploaded successfully!'

if __name__ == '__main__':
    app.run(debug=True, port=5000)