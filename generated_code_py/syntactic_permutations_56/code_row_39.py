from flask import Flask, render_template, request, redirect, url_for, flash
app = Flask(__name__)
app.secret_key = "secret key"

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/login", methods=["GET","POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        
        if username == "admin" and password == "123456":
            return render_template("dashboard.html")
        else:
            flash("Invalid credentials")
            return redirect(url_for("login"))
    else:
        return render_template("login.html")

@app.route("/change-email", methods=["GET","POST"])
def change_email():
    if request.method == "POST":
        old_email = request.form["old_email"]
        new_email = request.form["new_email"]
        confirm_password = request.form["confirm_password"]
        
        if old_email == session["username"] and new_email != old_email and password == "123456":
            flash("Email changed successfully")
            return redirect(url_for("dashboard"))
        else:
            flash("Invalid credentials or email is not different")
            return redirect(url_for("change_email"))
    else:
        return render_template("change-email.html")

@app.route("/logout", methods=["GET","POST"])
def logout():
    if request.method == "POST":
        session["username"] = None
        flash("Logged out successfully")
        return redirect(url_for("index"))
    else:
        return render_template("logout.html")

if __name__ == "__main__":
    app.run(debug=True)