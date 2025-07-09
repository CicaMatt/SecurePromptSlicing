import json
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy
import os

app = Flask(__name__)

# setup sql alchemy
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///email_list.db"
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False
db = SQLAlchemy(app)

# create the email table in the database
class Email(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)

    def __repr__(self):
        return f"Email('{self.email}')"

# create the database if it doesn't exist
db.create_all()

@app.route("/", methods=["GET"])
def unsubscribe():
    email = request.args.get("email")
    user = Email.query.filter_by(email=email).first()

    # check if the user is in the database
    if user:
        db.session.delete(user)
        db.session.commit()
        return "You have been unsubscribed."
    else:
        return "You are not subscribed."

if __name__ == "__main__":
    app.run(debug=True)