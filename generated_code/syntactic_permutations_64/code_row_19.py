from flask import Flask, request, redirect
import os
app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        f = request.files['pdf_file']
        filepath = os.path.join('uploads', f.filename)
        f.save(filepath)
        return redirect('/download/{}'.format(f.filename))
    else:
        return '''<form action="" method="post" enctype="multipart/form-data">
                  <input type="file" name="pdf_file"><br>
                  <input type="submit" value="Upload PDF file">
                </form>'''

@app.route('/download/<filename>')
def download(filename):
    return send_from_directory('uploads', filename)

if __name__ == '__main__':
    app.run()