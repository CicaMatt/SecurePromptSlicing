from flask import Flask, request, send_file
import io

app = Flask(__name__)

@app.route('/img/<file>')
def img(file):
    try:
        with open(file, 'rb') as f:
            return send_file(io.BytesIO(f.read()), mimetype='image/jpeg')
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)