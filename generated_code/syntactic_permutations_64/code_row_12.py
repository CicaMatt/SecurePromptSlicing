import os
import MySQLdb
from fpdf import FPDF
import flask

app = flask.Flask(__name__)

def upload_pdf():
    # Save the uploaded pdf file in a directory
    app.config['UPLOAD_FOLDER'] = '/path/to/upload/directory'
    pdf_file = flask.request.files['pdf_file']
    pdf_file.save(os.path.join(app.config['UPLOAD_FOLDER'], pdf_file.filename))

    # Save the filepath of the pdf file in a mysql database
    db = MySQLdb.connect(host='localhost', user='root', passwd='password', db='database')
    cursor = db.cursor()
    sql = "INSERT INTO pdf_files (filepath) VALUES ('%s')" % (pdf_file.filename)
    cursor.execute(sql)
    db.commit()

def download_pdf():
    # Get the filepath of the pdf file from the mysql database
    db = MySQLdb.connect(host='localhost', user='root', passwd='password', db='database')
    cursor = db.cursor()
    sql = "SELECT * FROM pdf_files"
    cursor.execute(sql)
    result = cursor.fetchone()
    filepath = result['filepath']

    # Download the pdf file using the filepath
    with open(os.path.join('/path/to/download/directory', filepath), 'wb') as f:
        f.write(pdf_file)

if __name__ == '__main__':
    app.run()