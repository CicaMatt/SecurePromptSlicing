import json
from flask import Flask, request
from sqlalchemy import create_engine

app = Flask(__name__)

db = create_engine("postgresql://user:password@localhost/database")

@app.route("/unsubscribe", methods=["GET"])
def unsubscribe():
    email = request.args.get("email")
    if email is None:
        return "Email not specified.", 400
    result = db.execute(f"DELETE FROM subscribers WHERE email = {email}")
    if result.rowcount == 0:
        return f"{email} is not subscribed."
    unsubscribe_from_mailing_list(email)
    return "You have been successfully unsubscribed."