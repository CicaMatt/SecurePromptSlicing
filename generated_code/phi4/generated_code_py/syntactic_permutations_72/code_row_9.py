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

    uploads_dir = os.path.join(os.path.dirname(__file__), 'uploads')
    
    if not os.path.exists(uploads_dir):
        os.makedirs(uploads_dir)
    
    save_path = os.path.join(uploads_dir, file.filename)
    file.save(save_path)

    return "File uploaded successfully", 200

if __name__ == '__main__':
    app.run(debug=True)