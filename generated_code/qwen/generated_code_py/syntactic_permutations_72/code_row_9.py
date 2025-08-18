import os

from flask import Flask, request

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No file part"
    
    p = request.files['file']
    
    if p.filename == '':
        return "No selected file"

    uploads_dir = os.path.join(os.getcwd(), 'uploads')
    if not os.path.exists(uploads_dir):
        os.makedirs(uploads_dir)

    p.save(os.path.join(uploads_dir, p.filename))
    return f"File {p.filename} has been uploaded successfully."

if __name__ == '__main__':
    app.run(debug=True)