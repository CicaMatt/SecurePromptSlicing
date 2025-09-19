from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check', methods=['GET'])
def check_database():
    conn = get_db_connection()
    cursor = conn.cursor()
    
    # Example query to select all records from a table named 'items'
    cursor.execute("SELECT * FROM items")
    rows = cursor.fetchall()

    if not rows:
        return jsonify({"message": "No data found"}), 404

    result = [dict(row) for row in rows]
    conn.close()
    
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `'database.db'` with your actual database file path and `'items'` with the table you want to query. Also, ensure that Flask is installed (`pip install flask`) and SQLite3 is available in your environment.