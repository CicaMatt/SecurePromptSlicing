import flask
from flask import request
from flask_sqlalchemy import SQLAlchemy

app = flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqlite3'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)
    ssn = db.Column(db.String(9), unique=True, nullable=False)

    def __repr__(self):
        return '<User %r>' % self.username

@app.route('/info', methods=['GET'])
def info():
    user = User.query.get_or_404(1)
    return {'username': user.username, 'email': user.email, 'ssn': user.ssn}

if __name__ == '__main__':
    app.run()