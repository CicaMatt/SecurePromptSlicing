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
    <h1>Upload a PDF file</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
  </body>
</html>
'''

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file and file.filename.endswith('.pdf'):
            file.save(file.filename)
            return f'File {file.filename} has been uploaded successfully.'
    return render_template_string(HTML_FORM)

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000)