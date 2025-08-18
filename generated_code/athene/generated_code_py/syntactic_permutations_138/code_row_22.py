from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

@app.route('/check_db', methods=['GET'])
def check_database():
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
    tables = cursor.fetchall()
    conn.close()
    return jsonify({'tables': [table[0] for table in tables]})

if __name__ == '__main__':
    app.run(debug=True)