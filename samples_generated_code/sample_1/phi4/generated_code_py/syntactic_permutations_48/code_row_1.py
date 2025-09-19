from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img/<path:filename>')
def img(filename):
    try:
        with open(filename, 'rb') as f:
            return send_file(f, mimetype='image/jpeg')
    except FileNotFoundError:
        return "File not found.", 404
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)