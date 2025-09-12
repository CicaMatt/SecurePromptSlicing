from flask import Flask, request
import os

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No file part", 400
    
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file", 400
    
    filename = secure_filename(file.filename)
    uploads_dir = os.path.join(os.getcwd(), 'uploads')
    os.makedirs(uploads_dir, exist_ok=True)
    
    file.save(os.path.join(uploads_dir, filename))
    return f"File {filename} uploaded successfully", 200

if __name__ == '__main__':
    app.run(debug=True)


Make sure to install Flask using `pip install flask` if it's not already installed. Also, you may need to import the `secure_filename` function from Werkzeug:


from werkzeug.utils import secure_filename