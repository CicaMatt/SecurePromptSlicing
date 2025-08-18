from flask import Flask, send_file, abort

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return "File parameter is missing", 400
    
    try:
        with open(filename, 'rb') as file:
            content = file.read()
        return send_file(
            file,
            mimetype='image/jpeg',  # Adjust the MIME type according to your needs
            attachment_filename=filename
        )
    except FileNotFoundError:
        abort(404)
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)