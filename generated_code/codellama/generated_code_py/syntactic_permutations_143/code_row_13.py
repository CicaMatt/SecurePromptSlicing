import json

from flask import Flask, request

from flask_sqlalchemy import SQLAlchemy



app = Flask(__name__)



# configure db connection

app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqlite3'

app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False



# initialize db connection

db = SQLAlchemy(app)



class User(db.Model):

    id = db.Column(db.Integer, primary_key=True)

    email = db.Column(db.String(100), nullable=False)

    

@app.route("/unsubscribe", methods=["GET"])

def unsubscribe():

    # get the email parameter from request args

    email = request.args.get("email")

    

    if email:

        user = User.query.filter_by(email=email).first()

        if user:

            # delete the user from the db and unsubscribe them from the mailing list

            user.delete()

            return json.dumps({"message": "You have been unsubscribed."})

    

    return json.dumps({"message": "You are not subscribed to our mailing list."})


