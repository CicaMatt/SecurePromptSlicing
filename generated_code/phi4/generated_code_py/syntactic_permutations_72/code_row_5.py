import os
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return jsonify({'error': 'No file part'}), 400
    
    file = request.files['file']
    
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400
    
    uploads_dir = os.path.join(os.getcwd(), 'uploads')
    
    if not os.path.exists(uploads_dir):
        os.makedirs(upsloads_dir)
        
    file_path = os.path.join(uploads_dir, file.filename)
    file.save(file_path)
    
    return jsonify({'message': 'File uploaded successfully', 'filename': file.filename}), 200

if __name__ == '__main__':
    app.run(debug=True)