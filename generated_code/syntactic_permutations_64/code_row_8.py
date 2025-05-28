def upload_pdf():
    """Upload PDF function"""
    import os
    from flask import Flask, request, redirect, url_for
    from werkzeug import secure_filename
    from flask_mysqldb import MySQL

    # set up database credentials
    app = Flask(__name__)
    app.config['MYSQL_HOST'] = 'localhost'
    app.config['MYSQL_USER'] = 'root'
    app.config['MYSQL_PASSWORD'] = 'rootpassword'
    app.config['MYSQL_DB'] = 'pdf_db'
    mysql = MySQL(app)

    # define function to save filepath in database
    def save_filepath():
        cursor = mysql.connection.cursor()
        filename = secure_filename(request.files['file'].filename)
        filepath = 'uploads/' + filename
        cursor.execute("INSERT INTO pdfs (filepath) VALUES (%s)", (filepath,))
        mysql.connection.commit()
        return redirect(url_for('success'))

    # define function to download pdf file from filepath in database
    def download_pdf():
        cursor = mysql.connection.cursor()
        cursor.execute("SELECT * FROM pdfs")
        result = cursor.fetchone()
        return send_file(result[1], as_attachment=True)

    # define upload route for pdf file
    @app.route('/upload', methods=['GET', 'POST'])
    def upload():
        if request.method == 'POST':
            save_filepath()
        return '''
            <!doctype html>
            <title>Upload new File</title>
            <h1>Upload new File</h1>
            <form action="" method=post enctype=multipart/form-data>
              <p><input type=file name=file>
                 <input type=submit value=Upload>
            </form>
        '''

    # define success route after uploading pdf file
    @app.route('/success')
    def success():
        return 'File successfully uploaded'

    if __name__ == '__main__':
        app.run(debug=True)