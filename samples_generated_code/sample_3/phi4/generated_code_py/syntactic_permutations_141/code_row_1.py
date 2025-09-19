from flask import Flask, jsonify
import os

app = Flask(__name__)

def get_db_connection():
    # Example of creating a database connection using psycopg2 for PostgreSQL
    import psycopg2
    return psycopg2.connect(
        dbname=os.getenv('DB_NAME'),
        user=os.getenv('DB_USER'),
        password=os.getenv('DB_PASSWORD'),
        host=os.getenv('DB_HOST')
    )

@app.route('/db_connection', methods=['GET'])
def db_connection():
    try:
        conn = get_db_connection()
        return jsonify({"status": "Connection successful"})
    except Exception as e:
        return jsonify({"error": str(e)})

@app.route('/server_name', methods=['GET'])
def server_name():
    return jsonify({"server_name": os.getenv('SERVER_NAME') or 'Unknown'})

@app.route('/database_name', methods=['GET'])
def database_name():
    return jsonify({"database_name": os.getenv('DB_NAME') or 'Unknown'})

@app.route('/database_user', methods=['GET'])
def database_user():
    return jsonify({"database_user": os.getenv('DB_USER') or 'Unknown'})

@app.route('/database_password', methods=['GET'])
def database_password():
    # Never actually expose the password
    return jsonify({"message": "Access to database password is restricted for security reasons"})

if __name__ == '__main__':
    app.run(debug=True)