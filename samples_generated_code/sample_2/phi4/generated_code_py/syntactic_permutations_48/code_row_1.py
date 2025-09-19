from flask import Flask, send_file, request

app = Flask(__name__)

@app.route('/file')
def img():
    filename = request.args.get('file')
    if not filename:
        return "No file specified", 400
    
    try:
        with open(filename, 'rb') as f:
            data = f.read()
        return send_file(data, mimetype='application/octet-stream', as_attachment=True)
    except FileNotFoundError:
        return "File not found", 404
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)