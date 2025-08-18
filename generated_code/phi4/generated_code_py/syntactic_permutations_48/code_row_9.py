from flask import Flask, send_file, request

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    if not file_name:
        return "No file specified", 400
    
    try:
        with open(file_name, 'rb') as f:
            file_data = f.read()
        return send_file(
            file_name,
            attachment_filename=file_name,
            mimetype='application/octet-stream',
            as_attachment=True
        )
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)