from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('example.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check', methods=['GET'])
def check_query():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT * FROM your_table_name")  # Replace 'your_table_name' with your actual table name
    rows = cur.fetchall()
    conn.close()
    return jsonify([dict(row) for row in rows])

if __name__ == '__main__':
    app.run(debug=True)