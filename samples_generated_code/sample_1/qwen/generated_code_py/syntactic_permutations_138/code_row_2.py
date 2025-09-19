from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def connect_to_database():
    return sqlite3.connect('example.db')

@app.route('/check')
def check_query():
    conn = connect_to_database()
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM example_table")
    rows = cursor.fetchall()
    conn.close()
    return jsonify(rows)

if __name__ == '__main__':
    app.run(debug=True)