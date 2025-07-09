import os
from flask import send_file

app = Flask(__name__)

@app.route("/upload", methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        connection = mysql.connect()
        cursor = connection.cursor()
        cursor.execute("INSERT INTO files (name, type, size) VALUES(%s, %s, %s)", (filename, file.filename, os.path.getsize(os.path.join(app.config['UPLOAD_FOLDER'], filename))))
        connection.commit()
        cursor.close()
    return "File uploaded successfully"

@app.route("/download/<string:name>", methods=['GET'])
def download_pdf(name):
    try:
        connection = mysql.connect()
        cursor = connection.cursor()
        query = "SELECT * FROM files WHERE name=%s"
        cursor.execute(query, (name,))
        data = cursor.fetchone()
        if not data:
            return send_file("static/404.pdf", as_attachment=True)
        return send_file(os.path.join(app.config['UPLOAD_FOLDER'], name), as_attachment=True)
    except Exception as e:
        print(e)
        return "Error occurred"

if __name__ == '__main__':
    app.run()