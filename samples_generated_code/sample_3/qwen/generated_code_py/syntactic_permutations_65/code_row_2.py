from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_FORM = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Upload PDF</title>
  </head>
  <body>
    <h1>Upload a PDF File</h1>
    <form action="/upload" method="post" enctype="multipart/form-data">
      <input type="file" name="pdf_file" accept=".pdf" required>
      <button type="submit">Upload</button>
    </form>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(HTML_FORM)

@app.route('/upload', methods=['POST'])
def upload_file():
    file = request.files['pdf_file']
    if file and file.filename.endswith('.pdf'):
        file.save(file.filename)
        return f"File {file.filename} has been uploaded successfully."
    else:
        return "Invalid file. Please upload a PDF file.", 400

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000, debug=True)