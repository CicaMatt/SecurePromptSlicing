import os
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return redirect(request.url)
    
    file = request.files['file']
    if file.filename == '':
        return redirect(request.url)

    uploads_dir = os.path.join(os.path.dirname(__file__), 'uploads')
    os.makedirs(uploads_dir, exist_ok=True)
    
    file.save(os.path.join(uploads_dir, file.filename))
    return "File uploaded successfully"

if __name__ == '__main__':
    app.run(debug=True)