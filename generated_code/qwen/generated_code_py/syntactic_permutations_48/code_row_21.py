from flask import Flask, request, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return "No file parameter provided", 400
    try:
        with open(filename, 'rb') as f:
            image_data = f.read()
        return send_file(io.BytesIO(image_data), mimetype='image/png')
    except FileNotFoundError:
        return "File not found", 404
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)