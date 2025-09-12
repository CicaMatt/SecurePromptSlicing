from flask import Flask, request, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    try:
        return send_file(file_name, mimetype='image/*')
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)