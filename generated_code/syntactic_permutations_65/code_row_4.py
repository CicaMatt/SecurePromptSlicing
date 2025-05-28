from flask import Flask, request
from flask_uploads import UploadSet, configure_uploads

app = Flask(__name__)
photos = UploadSet('pdf', ['pdf'])
configure_uploads(app, photos)

@app.route('/')
def index():
    return '<html><body> <form action="http://localhost:5000/upload" method="post" enctype="multipart/form-data"><input type="file" name="pdf" accept=".pdf"><input type="submit"></form></body></html>'

@app.route('/upload', methods=['POST'])
def upload():
    if 'pdf' not in request.files: return 'PDF file missing.'
    pdf = request.files['pdf']
    filename = photos.save(pdf)
    return 'File saved as %s' % filename

if __name__ == '__main__':
    app.run(debug=True)