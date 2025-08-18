from flask import Flask, send_file, request

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return "File parameter missing", 400
    
    try:
        with open(filename, 'rb') as file:
            content = file.read()
        return send_file(
            file=content,
            mimetype='image/jpeg',  # Change the MIME type based on your image format
            as_attachment=True,
            attachment_filename=filename
        )
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)