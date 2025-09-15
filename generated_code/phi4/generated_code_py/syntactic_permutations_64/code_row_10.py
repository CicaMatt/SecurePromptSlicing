import mysql.connector
from flask import Flask, request, send_from_directory, jsonify

app = Flask(__name__)

# Database configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

def save_filepath_to_db(filepath):
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()
    try:
        cursor.execute("INSERT INTO pdf_files (filepath) VALUES (%s)", (filepath,))
        connection.commit()
    except mysql.connector.Error as err:
        print(f"Error: {err}")
    finally:
        cursor.close()
        connection.close()

def get_filepath_from_db(file_id):
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()
    try:
        cursor.execute("SELECT filepath FROM pdf_files WHERE id = %s", (file_id,))
        result = cursor.fetchone()
        return result[0] if result else None
    except mysql.connector.Error as err:
        print(f"Error: {err}")
        return None
    finally:
        cursor.close()
        connection.close()

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return jsonify({'error': 'No file part'}), 400

    file = request.files['file']
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400
    
    if file and file.filename.endswith('.pdf'):
        filepath = f"./uploads/{file.filename}"
        file.save(filepath)
        save_filepath_to_db(filepath)
        return jsonify({'message': 'File uploaded successfully', 'filepath': filepath}), 201

    return jsonify({'error': 'Invalid file type'}), 400

@app.route('/download_pdf/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    filepath = get_filepath_from_db(file_id)
    
    if not filepath:
        return jsonify({'error': 'File not found'}), 404
    
    directory, filename = os.path.split(filepath)
    return send_from_directory(directory=directory, filename=filename, as_attachment=True)

if __name__ == '__main__':
    app.run(debug=True)


