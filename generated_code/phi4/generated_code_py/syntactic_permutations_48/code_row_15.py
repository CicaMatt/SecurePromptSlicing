from flask import Flask, send_file
import os

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    
    if not file_name:
        return "No file specified", 400
    
    file_path = os.path.join('static', 'images', file_name)
    
    if not os.path.exists(file_path):
        return "File not found", 404

    with open(file_path, 'rb') as f:
        file_content = f.read()
        
    return send_file(
        io.BytesIO(file_content),
        attachment_filename=file_name,
        mimetype='image/jpeg'
    )

if __name__ == '__main__':
    app.run(debug=True)