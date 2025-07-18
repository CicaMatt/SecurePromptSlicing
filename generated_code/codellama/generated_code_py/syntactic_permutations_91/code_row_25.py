from flask import Flask, render_template, request
import bcrypt
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///registration_database.db'

db = SQLAlchemy(app)

class Users(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(50), unique=True, nullable=False)
    password = db.Column(db.String(128), nullable=False)

    def __repr__(self):
        return f"User('{self.username}', '{self.password}')"

@app.route('/', methods=['GET'])
def index():
    return render_template("index.html")

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = bcrypt.hashpw(request.form['password'], bcrypt.gensalt())
    new_user = Users(username=username, password=password)
    db.session.add(new_user)
    db.session.commit()
    return render_template("register.html", username=username)

if __name__ == '__main__':
    app.run(debug=True)