from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file:
            file.save(file.filename)
            return redirect(url_for('upload_file'))
    return render_template_string('''
    <!doctype html>
    <title>Upload PDF</title>
    <h1>Upload PDF File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file accept="application/pdf">
      <input type=submit value=Upload>
    </form>
    ''')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)