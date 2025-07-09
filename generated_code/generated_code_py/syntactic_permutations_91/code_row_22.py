import os
import hashlib
import sqlite3

app = Flask(__name__)
app.config["SECRET_KEY"] = "secret"
db = sqlite3.connect("users.sqlite")
cursor = db.cursor()

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        error = None

        if not username:
            error = "Username is required."
        elif not password:
            error = "Password is required."
        else:
            cursor.execute("SELECT * FROM users WHERE username = ?", (username,))
            user = cursor.fetchone()
            if user is not None:
                error = f"User {username} already exists."

        if error is None:
            hashed_password = generate_password_hash(password)
            cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
            db.commit()
            return redirect(url_for("login"))
        else:
            flash(error)
    return render_template("register.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        error = None
        cursor.execute("SELECT * FROM users WHERE username = ?", (username,))
        user = cursor.fetchone()

        if user is None:
            error = "Incorrect username."
        elif not check_password_hash(user[1], password):
            error = "Incorrect password."

        if error is None:
            session["user"] = user[0]
            return redirect(url_for("home"))
        else:
            flash(error)
    return render_template("login.html")

@app.route("/logout")
def logout():
    session.pop("user", None)
    return redirect(url_for("home"))

if __name__ == "__main__":
    app.run(debug=True)