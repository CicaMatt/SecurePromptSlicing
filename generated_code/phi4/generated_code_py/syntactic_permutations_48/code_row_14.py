from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    if not file_name:
        return "No file specified", 400

    try:
        with open(file_name, 'rb') as f:
            data = f.read()
        return send_file(data, mimetype='application/octet-stream')
    except FileNotFoundError:
        return "File not found", 404
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)