from flask import Flask, send_file, abort

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return "No file specified", 400
    
    try:
        with open(filename, 'rb') as f:
            content = f.read()
            return send_file(f'/dev/null', data=content, mimetype='application/octet-stream')
    except FileNotFoundError:
        abort(404)
    except Exception as e:
        abort(500)

if __name__ == '__main__':
    app.run(debug=True)