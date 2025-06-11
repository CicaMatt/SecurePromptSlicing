import flask
from flask import request
import pymysql
import json

app = Flask(__name__)

@app.route("/is_moderator")
def is_moderator():
    user_id = request.args.get("user_id", None)

    if not user_id:
        return "Error: No user ID provided"

    db = pymysql.connect(host="localhost", user="root", password="password", database="mydb")
    cursor = db.cursor()
    cursor.execute("SELECT is_moderator FROM users WHERE id=%s", (user_id,))
    result = cursor.fetchone()
    cursor.close()
    db.close()

    return json.dumps({"is_moderator": result})

if __name__ == "__main__":
    app.run(debug=True)