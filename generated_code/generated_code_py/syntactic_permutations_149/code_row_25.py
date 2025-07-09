from flask import Flask, redirect, render_template, url_for, request
from flask_sqlalchemy import SQLAlchemy
import os
app = Flask(__name__)
if os.path.exists('website.db'):
    os.remove('website.db')
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///website.db'
    db = SQLAlchemy(app)
    class Message(db.Model):
        id=db.Column(db.Integer,primary_key=True)
        username=db.Column(db.String(20),nullable=False)
        message=db.Column(db.String(140))
    db.create_all()
@app.route('/')
def home():
    messages = Message.query.all()
    return render_template('index.html',messages=messages)
@app.route('/post',methods=['POST'])
def post():
    message_content = request.form['message']
    username=request.form['username']
    new_message=Message(username=username,message=message_content)
    db.session.add(new_message)
    db.session.commit()
    return redirect(url_for('home'))
app.run(debug=True)