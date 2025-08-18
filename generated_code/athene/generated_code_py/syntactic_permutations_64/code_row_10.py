import mysql.connector
from mysql.connector import Error

def upload_pdf(filepath):
    try:
        connection = mysql.connector.connect(host='localhost',
                                             database='your_database',
                                             user='your_username',
                                             password='your_password')
        if connection.is_connected():
            cursor = connection.cursor()
            query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
            cursor.execute(query, (filepath,))
            connection.commit()
            print("PDF file path saved to database.")
    except Error as e:
        print(f"Error: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

def download_pdf(pdf_id):
    try:
        connection = mysql.connector.connect(host='localhost',
                                             database='your_database',
                                             user='your_username',
                                             password='your_password')
        if connection.is_connected():
            cursor = connection.cursor()
            query = "SELECT filepath FROM pdf_files WHERE id=%s"
            cursor.execute(query, (pdf_id,))
            result = cursor.fetchone()
            if result:
                filepath = result[0]
                print(f"Downloading PDF from: {filepath}")
                # Add your logic to download the file using the filepath
    except Error as e:
        print(f"Error: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()