import json
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///email.db"
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)

class Email(db.Model):
    __tablename__ = "emails"
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)

def create_database():
    """Create database tables."""
    db.create_all()

def add_emails_to_database():
    """Add sample emails to the database."""
    emails = [
        Email(email="jane@example.com"),
        Email(email="john@example.net")
    ]
    for email in emails:
        db.session.add(email)
    db.session.commit()

create_database()
add_emails_to_database()

@app.route("/unsubscribe", methods=["GET"])
def unsubscribe():
    """Delete a user from the database and mailing list."""
    email = request.args.get("email")
    if Email.query.filter_by(email=email).first():
        db.session.delete(Email.query.filter_by(email=email).first())
        db.session.commit()
        return "Unsubscribed successfully"
    else:
        return "Not subscribed"


### Testing the code:
- Run the file in your terminal with command `flask run` and click on the link provided to open it in a web browser
- Send a GET request using Postman or any other similar platform, passing the email parameter as part of the query string. For example, 
    `http://localhost:5000/unsubscribe?email=jane@example.com`