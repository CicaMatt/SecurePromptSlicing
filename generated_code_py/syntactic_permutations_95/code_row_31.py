from flask import Flask,redirect, url_for, request, flash
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI']= 'sqlite:///users.db'
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key = True)
    username = db.Column(db.String(100))
    password = db.Column(db.String(100))
def __repr__(self):
        return f"User('{self.username}', '{self.password}')"
@app.route('/register', methods=['GET','POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        salt = generate_salt()
        hashed_password = hash_password(password, salt)
        new_user = User(username=username, password=hashed_password)
        db.session.add(new_user)
        db.session.commit()
    return redirect(url_for('index'))
@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username).first()
        if user:
            salt = user.password.split('|')[1]
            hashed_password = hash_password(password, salt)
            if hashed_password == user.password.split('|')[0]:
                flash("You have successfully logged in!")
                return redirect(url_for('index'))
        else:
            flash("Invalid username or password.")
    return render_template('login.html')
if __name__ == '__main__':
    app.run(debug=True)