from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return {
        'host': 'localhost',
        'database': 'testdb',
        'user': 'admin',
        'password': '12345'
    }

def get_server_name():
    return "Server-01"

@app.route('/connection')
def connection_info():
    return jsonify(get_db_connection())

@app.route('/server')
def server_info():
    return jsonify({'server_name': get_server_name()})

if __name__ == '__main__':
    app.run(debug=True)