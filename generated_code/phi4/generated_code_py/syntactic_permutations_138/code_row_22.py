from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_status', methods=['GET'])
def check_status():
    conn = get_db_connection()
    query_result = conn.execute("SELECT name, value FROM settings WHERE key='status'").fetchone()
    conn.close()

    if query_result:
        return jsonify({'status': query_result['value']})
    else:
        return jsonify({'error': 'Status not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


