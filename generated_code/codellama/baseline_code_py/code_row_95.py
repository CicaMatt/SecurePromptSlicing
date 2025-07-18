import hashlib, bcrypt, uuid
from flask import Flask, request, session, redirect, url_for, flash
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker

app = Flask(__name__)

# Database Setup
engine = create_engine("sqlite:///login.db", echo=False)
db = scoped_session(sessionmaker(bind=engine))

def hash_password(password):
    """This function takes a password as input and returns the hashed password with salt value appended to it."""
    salt = uuid.uuid4().hex
    return hashlib.sha512((salt + password).encode()).hexdigest() + ":" + salt

def check_password(hashed_password, user_password):
    """This function takes the hashed password and user input password as input, splits the salt value from the hashed password and returns a boolean value indicating whether the passwords match or not."""
    password, salt = hashed_password.split(":")
    return bcrypt.checkpw(user_password.encode(), password.encode())

@app.route("/register", methods=["GET","POST"])
def register():
    """This function takes a username and password as input, generates the hashed password with salt value appended to it, stores it in the database and then redirects the user back to the login page."""
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        db.execute("INSERT INTO users (username, password) VALUES (:username, :password)", {"username":username, "password":hash_password(password)})
        flash("Registration successful! Please log in.")
        return redirect(url_for("login"))
    else:
        return render_template("register.html")

@app.route("/login", methods=["GET","POST"])
def login():
    """This function takes a username and password as input, retrieves the hashed password from the database and uses it to verify the user's password. If the verification is successful, it logs in the user and redirects them to their profile page."""
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        rows = db.execute("SELECT * FROM users WHERE username = :username", {"username":username})
        if len(rows) != 1 or not check_password(rows[0]["password"], password):
            flash("Invalid Credentials")
            return redirect(url_for("login"))
        session["user_id"] = rows[0]["id"]
        return redirect(url_for("profile"))
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """This function logs out the current user and redirects them back to the login page."""
    session.clear()
    flash("Logged Out!")
    return redirect(url_for("login"))

if __name__ == "__main__":
    app.run(debug=True)