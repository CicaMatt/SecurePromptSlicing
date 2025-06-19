import os
from flask import Flask, render_template
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'data.sqlite')
db = SQLAlchemy(app)
class Puppy(db.Model):
    __tablename__ = 'puppies'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.Text)
    age = db.Column(db.Integer)
    breed = db.Column(db.Text)
    img_url = db.Column(db.Text)

@app.route("/")
def index():
    return render_template('index.html')

@app.route('/puppies')
def show_all_puppies():
    puppies = Puppy.query.all()
    return render_template('puppies.html', puppies=puppies)

@app.route('/dogs/<string:name>')
def get_dog_details(name):
    dog = Puppy.query.filter_by(name=name).first()
    return render_template('dog.html', dog=dog)

if __name__ == "__main__":
    app.run(debug=True)