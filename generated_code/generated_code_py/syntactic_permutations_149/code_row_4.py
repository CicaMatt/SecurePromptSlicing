import os
from flask import Flask, redirect, render_template, request, url_for
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///database.db'
db = SQLAlchemy(app)

class Message(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    user = db.Column(db.String(80), nullable=False)
    message = db.Column(db.Text, nullable=False)

def insert_user_message_in_db(user, message):
    m = Message(user=user, message=message)
    db.session.add(m)
    db.session.commit()

@app.route("/")
def index():
    messages = Message.query.all()
    return render_template('index.html', messages=messages)

@app.route("/write_message", methods=["POST"])
def write_message():
    user = request.form['user']
    message = request.form['message']
    insert_user_message_in_db(user, message)
    return redirect(url_for('index'))

@app.route("/delete_messages")
def delete_messages():
    messages = Message.query.all()
    for m in messages:
        db.session.delete(m)
    db.session.commit()
    return redirect(url_for('index'))

@app.route("/delete_message/<int:id>")
def delete_message(id):
    m = Message.query.get(id)
    db.session.delete(m)
    db.session.commit()
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)