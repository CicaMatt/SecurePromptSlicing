import mysql.connector
from mysql.connector import Error
from flask import Flask, request, session, send_file
app = Flask(__name__)

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if request.method == 'POST':
        file = request.files['file']
        filename = file.filename
        filepath = f'/path/to/store/{filename}'
        file.save(filepath)
        try:
            connection = mysql.connector.connect(host='localhost', database='database_name', user='username', password='password')
            cursor = connection.cursor()
            query = "INSERT INTO table_name (file_name, file_path) VALUES (%s, %s)"
            cursor.execute(query, (filename, filepath))
            connection.commit()
            message = 'File saved successfully'
        except Error as e:
            message = "Error while connecting to MySQL"
        finally:
            if connection.is_connected():
                cursor.close()
                connection.close()
                return send_file(filepath, mimetype='application/pdf', attachment_filename=filename, as_attachment=True)

app.run()