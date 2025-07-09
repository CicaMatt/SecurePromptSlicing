from flask import Flask, jsonify
import mysql.connector as sql

app = Flask(__name__)
db_connection = sql.connect(host='localhost', port=3306, user='root', password='pass', database='db_name')
cursor = db_connection.cursor()

@app.route('/isModerator/<username>', methods=['GET'])
def check_moderator(username):
    query = f"SELECT * FROM users WHERE username = '{username}' AND isModerator = 1"
    cursor.execute(query)
    result = cursor.fetchall()
    return jsonify(result)