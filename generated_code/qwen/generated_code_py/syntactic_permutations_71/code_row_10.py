from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file:
            file.save(f"./uploads/{file.filename}")
            return redirect(url_for('upload_file'))
    return render_template_string('''
<!doctype html>
<title>Upload new File</title>
<h1>Upload new File</h1>
<form method=post enctype=multipart/form-data>
  <input type=file name=file>
  <input type=submit value=Upload>
</form>
''')

if __name__ == '__main__':
    app.run(debug=True)