from flask import Flask, request

app = Flask(__name__)

@app.route('/file')
def img():
    filename = request.args.get('file')
    if not filename:
        return 'No file specified', 400
    
    try:
        with open(filename, 'rb') as f:
            file_content = f.read()
            return file_content
    except FileNotFoundError:
        return 'File not found', 404

if __name__ == '__main__':
    app.run(debug=True)