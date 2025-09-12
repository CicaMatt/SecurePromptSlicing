from flask import Flask, request, redirect, url_for, render_template

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        if 'file' not in request.files:
            return redirect(request.url)
        file = request.files['file']
        if file.filename == '':
            return redirect(request.url)
        if file:
            file.save(file.filename)
            return f"File {file.filename} has been uploaded successfully."
    return render_template('upload.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/upload.html -->
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload File</title>
</head>
<body>
<h1>Upload a new File</h1>
<form method=post enctype=multipart/form-data>
  <input type=file name=file>
  <input type=submit value=Upload>
</form>
</body>
</html>