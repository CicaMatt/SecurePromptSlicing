from flask import Flask, jsonify
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host='localhost',
        database='your_database_name',
        user='your_username',
        password='your_password'
    )
    return conn

@app.route('/check', methods=['GET'])
def check_query():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute('SELECT * FROM your_table_name LIMIT 1;')
    result = cur.fetchone()
    cur.close()
    conn.close()
    if result:
        return jsonify({'status': 'success', 'data': result})
    else:
        return jsonify({'status': 'no data'})

if __name__ == '__main__':
    app.run(debug=True)