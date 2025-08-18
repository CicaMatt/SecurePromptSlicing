from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    try:
        with open(file_name, 'rb') as f:
            return send_file(f, mimetype='image/jpeg', as_attachment=True)
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)