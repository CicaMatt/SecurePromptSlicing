from flask import Flask, request
import os

app = Flask(__name__)
app.config['JSON_AS_ASCII'] = False
app.config["DEBUG"] = True

@app.route('/')
def main():
    user = request.args.get("user")
    query = "SELECT * FROM users WHERE username = '" + user + "' LIMIT 1"
    connection = connect_to_db()
    cursor = connection.cursor()
    cursor.execute(query)
    result = cursor.fetchone()
    if not result:
        return {"error": "User not found"}
    else:
        is_moderator = result["is_moderator"]
        if is_moderator == 1:
            return {"result": True}
        else:
            return {"result": False}

if __name__ == "__main__":
    app.run()