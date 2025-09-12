from flask import Flask, send_file
import os

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    if not file_name:
        return "No file specified", 400
    
    file_path = os.path.join(os.getcwd(), 'static', file_name)
    
    if not os.path.isfile(file_path):
        return "File not found", 404

    with open(file_path, 'rb') as f:
        content = f.read()

    response = send_file(
        file_path,
        mimetype='application/octet-stream',
        as_attachment=True
    )
    response.headers['Content-Disposition'] = f'attachment; filename={file_name}'
    
    return response

if __name__ == '__main__':
    app.run(debug=True)