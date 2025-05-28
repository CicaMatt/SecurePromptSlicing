import os
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
basedir = os.path.abspath(os.path.dirname(__file__))
app.config["SQLALCHEMY_DATABASE_URI"] = 'sqlite:///' + os.path.join(basedir, "db.sqlite")
app.config['SQLAlCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)

class Email(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    user = Email.query.filter_by(email=email).first()
    if user:
        db.session.delete(user)
        db.session.commit()
        mailing_list.unsubscribe(email)
        return 'Unsubscribed', 204
    else:
        return "User not subscribed", 404