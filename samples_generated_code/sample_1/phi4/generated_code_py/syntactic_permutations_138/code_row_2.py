from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('example.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_database', methods=['GET'])
def check_database():
    conn = get_db_connection()
    cursor = conn.cursor()
    
    # Example query to check the database (e.g., count rows in a table)
    cursor.execute("SELECT COUNT(*) FROM your_table_name")
    row_count = cursor.fetchone()[0]

    conn.close()

    return jsonify({"row_count": row_count})

if __name__ == '__main__':
    app.run(debug=True)


Note: Make sure to replace `'your_table_name'` with the actual name of your table and ensure that `example.db` is replaced or created as per your database setup.