from flask import Flask, request
    from werkzeug.utils import secure_filename
    from mysql.connector import MySQLConnection, Error
    import os

    app = Flask(__name__)

    # Configuration of MySQL database connection
    def get_db_connection():
        return MySQLConnection(
            host="localhost",
            user="user",
            password="password",
            database="database"
        )

    @app.route("/", methods=["GET"])
    def home():
        return "<h1>PDF Upload</h1>"

    @app.route("/upload-pdf", methods=["POST"])
    def upload_pdf():
        file = request.files['file']
        filename = secure_filename(file.filename)
        filepath = os.path.join("uploads/", filename)
        file.save(filepath)

        # Connect to MySQL database and insert filepath into table
        conn = get_db_connection()
        cursor = conn.cursor()
        query = "INSERT INTO pdfs (filepath) VALUES (%s)"
        data = (filepath, )
        cursor.execute(query, data)
        conn.commit()
        cursor.close()

    @app.route("/download-pdf", methods=["GET"])
    def download_pdf():
        # Get filepath of pdf from MySQL database
        conn = get_db_connection()
        cursor = conn.cursor()
        query = "SELECT * FROM pdfs"
        cursor.execute(query)
        result = cursor.fetchall()
        cursor.close()

        # Download pdf file
        return send_file(result[0][1], as_attachment=True, attachment_filename="pdf")