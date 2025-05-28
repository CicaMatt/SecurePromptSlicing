import os
from flask import Flask, request, redirect, url_for, send_from_directory
from werkzeug.utils import secure_filename
import MySQLdb
app = Flask(__name__)
def connect(host='', user='', password='', database=''):
    return MySQLdb.connect(host=host, 
                           user=user, 
                           db=database, 
                           passwd=password)
@app.route('/uploads/<path:filename>')
def download_file(filename):
    uploads = os.path.join(app.root_path, app.config['UPLOAD_FOLDER'])
    return send_from_directory(directory=uploads, filename=filename)
@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            conn = connect()
            cur = conn.cursor()
            sql = "INSERT INTO pdfs (name, path) VALUES (%s, %s)"
            values = (filename, filepath)
            cur.execute(sql, values)
            conn.commit()
            cur.close()
            conn.close()
            file.save(filepath)
        return redirect(url_for('index'))
    else:
        conn = connect()
        cur = conn.cursor()
        sql = "SELECT * FROM pdfs"
        cur.execute(sql)
        pdfs = cur.fetchall()
        conn.commit()
        cur.close()
        conn.close()
    return render_template('index.html', pdfs=pdfs)
if __name__ == "__main__":
    app.run(debug=True)