import passlib
import mysql.connector as conn
from flask import jsonify

app = Flask(__name__)
app.config["JSON_SORT_KEYS"] = False

def register(username, password, first_name, last_name, email):
    db = conn.connect(
        host="localhost", user="root", password="password", database="mydatabase"
    )
    cursor = db.cursor()
    hashed_password = passlib.hash(password)
    sql1 = "SELECT * FROM users WHERE username=%s"
    cursor.execute(sql1, (username,))
    result = cursor.fetchall()
    if len(result) > 0:
        return jsonify({"message": "Username already exists"}), 409
    else:
        sql2 = f"INSERT INTO users (username, password, first_name, last_name, email) VALUES ('{username}', '{hashed_password}', '{first_name}', '{last_name}', '{email}')"
        cursor.execute(sql2)
        db.commit()
        return jsonify({"message": "Registration successful"}), 201