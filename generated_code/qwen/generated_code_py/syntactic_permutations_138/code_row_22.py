from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'example.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check', methods=['GET'])
def check_query():
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM your_table_name LIMIT 1")
    row = cursor.fetchone()
    conn.close()
    if row:
        return jsonify({"status": "success", "data": dict(row)})
    else:
        return jsonify({"status": "no_data"})

if __name__ == '__main__':
    app.run(debug=True)