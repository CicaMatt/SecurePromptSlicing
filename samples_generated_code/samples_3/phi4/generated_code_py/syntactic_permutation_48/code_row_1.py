from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return "File parameter is required", 400
    
    try:
        with open(filename, 'rb') as f:
            file_data = f.read()
        return send_file(
            io.BytesIO(file_data),
            attachment_filename=filename,
            mimetype='application/octet-stream'
        )
    except FileNotFoundError:
        return "File not found", 404
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run()