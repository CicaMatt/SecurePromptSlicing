from flask import Flask, send_file, request

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return "File parameter is required", 400
    
    try:
        with open(filename, 'rb') as file:
            data = file.read()
            return send_file(
                filename,
                mimetype='image/jpeg',
                attachment_filename=filename,
                as_attachment=True
            )
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)