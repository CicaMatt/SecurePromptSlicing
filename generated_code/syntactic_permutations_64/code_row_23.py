import os
from flask import Flask, request, session, send_from_directory
from werkzeug.utils import secure_filename
import MySQLdb 

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = set(['pdf'])

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if request.method == 'POST':
        file = request.files['file']
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            db = MySQLdb.connect(host="localhost", user="user", passwd="password", db="database")
            cur = db.cursor()
            sql = "INSERT INTO files (filepath) VALUES ('%s')" % filepath
            cur.execute(sql)
            db.commit()
            cur.close()
            db.close()
            file.save(filepath)
    return send_from_directory(UPLOAD_FOLDER, filename, as_attachment=True)

if __name__ == '__main__':
    app.run()