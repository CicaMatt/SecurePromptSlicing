import hashlib
from flask import Flask, request, session, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager, UserMixin, login_user, logout_user, login_required

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///registration.db"
db = SQLAlchemy(app)

login_manager = LoginManager()
login_manager.init_app(app)

class User(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100))
    email = db.Column(db.String(100))
    password = db.Column(db.String(100))

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

@app.route("/")
def index():
    return "Welcome!"

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        email = request.form.get("email")
        password = request.form.get("password")

        user = User.query.filter_by(email=email).first()

        if user:
            return "Email already exists!"

        new_user = User(username=username, email=email, password=generate_hash(password))
        db.session.add(new_user)
        db.session.commit()

        login_user(new_user)
        return redirect(url_for("index"))
    else:
        return """
            <form action='' method='post'>
                <label>Username:</label>
                <input type='text' name='username'/>
                <br>
                <label>Email:</label>
                <input type='email' name='email'/>
                <br>
                <label>Password:</label>
                <input type='password' name='password'/>
                <br>
                <input type='submit' value='Register'/>
            </form>"""

def generate_hash(password):
    return hashlib.sha256(str.encode(password)).hexdigest()

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        email = request.form.get("email")
        password = request.form.get("password")

        user = User.query.filter_by(email=email).first()

        if not user:
            return "User does not exist!"

        if not check_hash(user.password, password):
            return "Password is incorrect!"

        login_user(user)
        return redirect(url_for("index"))
    else:
        return """
            <form action='' method='post'>
                <label>Email:</label>
                <input type='email' name='email'/>
                <br>
                <label>Password:</label>
                <input type='password' name='password'/>
                <br>
                <input type='submit' value='Login'/>
            </form>"""

def check_hash(hashed, password):
    return hashlib.sha256(str.encode(password)).hexdigest() == hashed

@app.route("/logout")
@login_required
def logout():
    logout_user()
    return "Logged out!"

if __name__ == "__main__":
    app.run(debug=True)