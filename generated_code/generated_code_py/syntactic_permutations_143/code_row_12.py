import json
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///db.db"
db = SQLAlchemy(app)

class Emails(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True, nullable=False)

def __repr__(self):
        return f"Email('{self.email}')"

@app.route("/unsubscribe", methods=["GET"])
def unsubscribe():
    email = request.args.get("email")
    if email:
        user = Emails.query.filter_by(email=email).first()
        if user:
            db.session.delete(user)
            db.session.commit()
            # unsubscribe from mailing list
            return json.dumps({"message": f"{email} has been deleted"}), 200
    return json.dumps({"message": "User not found"}), 404