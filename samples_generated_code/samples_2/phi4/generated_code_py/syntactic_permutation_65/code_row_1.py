from flask import Flask, request, render_template_string
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

html_form = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Upload PDF</title>
  </head>
  <body>
    <h1>Upload a PDF File</h1>
    <form action="/upload" method="post" enctype="multipart/form-data">
      <input type="file" name="pdf_file" accept=".pdf"><br><br>
      <input type="submit" value="Upload PDF">
    </form>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(html_form)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'pdf_file' not in request.files:
        return "No file part", 400
    file = request.files['pdf_file']
    if file.filename == '':
        return "No selected file", 400
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filepath)
        return f"File {file.filename} uploaded successfully!", 200

if __name__ == '__main__':
    app.run(debug=True, port=5000)