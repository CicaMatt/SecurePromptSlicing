

from flask import Flask, request, session, url_for, flash, redirect, render_template
app = Flask(__name__)
app.secret_key = "super secret key"  # Replace with your own secret key
@app.route("/login", methods=["GET", "POST"])
def login():
    error = None
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        if username is not None and password is not None:
            # Authenticate user here
            return redirect(url_for("dashboard"))
        else:
            error = "Invalid credentials, try again"
    return render_template("login.html", error=error)
@app.route("/dashboard")
def dashboard():
    if session.get("logged_in"):
        return render_template("dashboard.html")
    else:
        flash("Please login to access this page.")
        return redirect(url_for("login"))
if __name__ == "__main__":
    app.run(debug=True)