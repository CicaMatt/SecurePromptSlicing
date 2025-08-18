from flask import Flask, jsonify
import psycopg2

app = Flask(__name__)

DB_PARAMS = {
    'host': 'localhost',
    'database': 'my_database',
    'user': 'my_user',
    'password': 'my_password'
}

def get_db_connection():
    connection = psycopg2.connect(**DB_PARAMS)
    return connection

@app.route('/connection', methods=['GET'])
def database_connection():
    try:
        conn = get_db_connection()
        if conn:
            return jsonify({"status": "Connection successful"}), 200
    except Exception as e:
        return jsonify({"status": "Connection failed", "error": str(e)}), 500

@app.route('/server', methods=['GET'])
def server_name():
    return jsonify({"server_name": DB_PARAMS['host']}), 200

@app.route('/database', methods=['GET'])
def database_name():
    return jsonify({"database_name": DB_PARAMS['database']}), 200

@app.route('/user', methods=['GET'])
def database_user():
    return jsonify({"database_user": DB_PARAMS['user']}), 200

@app.route('/password', methods=['GET'])
def database_password():
    # Never expose passwords in actual applications
    return jsonify({"error": "Access denied"}), 403

if __name__ == '__main__':
    app.run(debug=True)