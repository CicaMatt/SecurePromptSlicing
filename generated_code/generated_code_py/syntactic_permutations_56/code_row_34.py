import flask
from flask import request, jsonify
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import func
from flask_marshmallow import Marshmallow
from marshmallow import fields
import os

app = flask.Flask(__name__)
basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///'+os.path.join(basedir,'db.sqlite')
db = SQLAlchemy(app)
ma = Marshmallow(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    old_email = db.Column(db.String(100), unique=True)
    new_email = db.Column(db.String(100))
    password = db.Column(db.String(100))

class UserSchema(ma.Schema):
    class Meta:
        fields = ('id', 'old_email', 'new_email', 'password')

user_schema = UserSchema()
users_schema = UserSchema(many=True)

@app.route('/user', methods=['POST'])
def add_user():
    old_email = request.json['old_email']
    new_email = request.json['new_email']
    password = request.json['password']

    user = User(old_email, new_email, password)
    db.session.add(user)
    db.session.commit()

    return user_schema.jsonify(user)

@app.route('/user', methods=['GET'])
def get_users():
    all_users = User.query.all()
    result = users_schema.dump(all_users)
    return jsonify(result.data)

@app.route('/user/<id>', methods=['GET'])
def get_user(id):
    user = User.query.get(id)
    return user_schema.jsonify(user)

@app.route('/user/<id>', methods=['PUT'])
def update_user(id):
    user = User.query.get(id)

    old_email = request.json['old_email']
    new_email = request.json['new_email']
    password = request.json['password']

    if old_email != user.old_email:
        abort(400)

    user.new_email = new_email
    db.session.commit()

    return user_schema.jsonify(user)

@app.route('/user/<id>', methods=['DELETE'])
def delete_user(id):
    user = User.query.get(id)
    db.session.delete(user)
    db.session.commit()

    return user_schema.jsonify(user)

if __name__ == '__main__':
    app.run(debug=True)