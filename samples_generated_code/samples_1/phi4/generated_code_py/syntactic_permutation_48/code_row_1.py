from flask import Flask, request, send_file
import os

app = Flask(__name__)

@app.route('/file')
def file():
    filename = request.args.get('file')
    if not filename:
        return "No file specified", 400
    
    filepath = os.path.join(os.getcwd(), filename)
    
    try:
        with open(filepath, 'rb') as f:
            content = f.read()
        
        response = send_file(
            os.path.join(app.root_path, filename),
            mimetype='application/octet-stream',
            attachment_filename=filename,
            as_attachment=True
        )
        return response
    
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)