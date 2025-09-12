from flask import Flask, request, redirect, url_for, render_template_string
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file and file.filename.endswith('.pdf'):
            filepath = os.path.join(UPLOAD_FOLDER, file.filename)
            file.save(filepath)
            return redirect(url_for('upload_file'))
    return render_template_string('''
    <form method="post" enctype="multipart/form-data">
      <input type="file" name="file">
      <input type="submit" value="Upload PDF">
    </form>
    ''')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)