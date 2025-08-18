from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    if file_name:
        try:
            with open(file_name, 'rb') as f:
                return send_file(f, mimetype='application/octet-stream', as_attachment=True)
        except FileNotFoundError:
            return "File not found", 404
    else:
        return "No file specified", 400

if __name__ == '__main__':
    app.run(debug=True)