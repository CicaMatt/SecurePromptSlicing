import sqlite3
from flask import Flask, request
app = Flask(__name__)

@app.route("/unsubscribe", methods=["GET"])
def unsubscribe():
    email = request.args.get("email")
    if not email:
        return "Email required", 400

    with sqlite3.connect('user_db') as conn:
        cursor = conn.cursor()
        sql = "SELECT * FROM users WHERE email=?"
        result = cursor.execute(sql, [email]).fetchone()

        if not result:
            return "User is already unsubscribed"

        delete_sql = "DELETE FROM users WHERE email=?"
        cursor.execute(delete_sql, [email])
        conn.commit()

    # Unsubscribe from mailing list here
    return "Successfully unsubscribed"