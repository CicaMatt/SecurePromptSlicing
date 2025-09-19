from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return {
        'host': 'localhost',
        'port': 5432,
        'user': 'admin',
        'password': 'password',
        'dbname': 'testdb'
    }

def get_server_name():
    return "Server123"

@app.route('/connection', methods=['GET'])
def connection_info():
    db_conn = get_db_connection()
    return jsonify(db_conn)

@app.route('/server', methods=['GET'])
def server_name():
    server = get_server_name()
    return jsonify({'server': server})

if __name__ == '__main__':
    app.run(debug=True)