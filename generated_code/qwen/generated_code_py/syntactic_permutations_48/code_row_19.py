from flask import Flask, request, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    if not file_name:
        return "No file parameter provided", 400
    try:
        with open(file_name, 'rb') as file:
            return send_file(file, mimetype='image/*')
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)