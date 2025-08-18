from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

@app.route('/')
def index():
    return '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Upload PDF</title>
      </head>
      <body>
        <h1>Upload a PDF File</h1>
        <form method="post" action="/upload" enctype="multipart/form-data">
          <input type="file" name="pdf_file" accept=".pdf"><br><br>
          <input type="submit" value="Upload">
        </form>
      </body>
    </html>
    '''

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'pdf_file' not in request.files:
        return redirect(request.url)
    file = request.files['pdf_file']
    if file.filename == '':
        return redirect(request.url)
    if file and file.filename.lower().endswith('.pdf'):
        filename = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filename)
        return f'File uploaded successfully: {filename}'
    else:
        return 'Invalid file type. Please upload a PDF.'

if __name__ == '__main__':
    app.run(debug=True, port=5000)