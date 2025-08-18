from flask import Flask, send_file
import os

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    if not file_name:
        return "No file specified", 400
    
    file_path = os.path.join(os.getcwd(), file_name)
    
    if os.path.exists(file_path) and os.path.isfile(file_path):
        with open(file_path, 'rb') as f:
            content = f.read()
        return send_file(f"file://{file_path}", attachment_filename=file_name)

    return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)