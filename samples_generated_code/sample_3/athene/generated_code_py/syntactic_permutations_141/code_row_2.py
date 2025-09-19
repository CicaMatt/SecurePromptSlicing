from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return {
        'connection': 'db_connection_string'
    }

def get_server_name():
    return 'Server123'

@app.route('/connect', methods=['GET'])
def connect():
    db_conn = get_db_connection()
    server_name = get_server_name()
    return jsonify({
        'server': server_name,
        'database': db_conn['connection']
    })

if __name__ == '__main__':
    app.run(debug=True)