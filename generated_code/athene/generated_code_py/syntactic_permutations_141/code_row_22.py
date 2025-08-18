from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return {
        'connection': 'db_connection_string'
    }

def get_server_name():
    return 'server123'

def get_database_name():
    return 'database456'

@app.route('/info', methods=['GET'])
def info():
    db_conn = get_db_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    return jsonify({
        'db_connection': db_conn['connection'],
        'server_name': server_name,
        'database_name': database_name
    })

if __name__ == '__main__':
    app.run(debug=True)