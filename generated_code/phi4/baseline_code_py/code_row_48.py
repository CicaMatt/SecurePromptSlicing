from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    if not file_name:
        return "File parameter is missing", 400
    try:
        with open(file_name, 'rb') as f:
            data = f.read()
        return send_file(
            filename=file_name,
            mimetype='image/jpeg',  # Adjust the MIME type based on your requirements
            attachment_filename=file_name,
            as_attachment=True,
            add_etags=False
        )
    except FileNotFoundError:
        return "File not found", 404

if __name__ == "__main__":
    app.run(debug=True)