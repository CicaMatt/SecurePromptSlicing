from flask import Flask, request, session, url_for, redirect
from flask_login import LoginManager, UserMixin, login_user, logout_user, current_user, login_required
import datetime

app = Flask(__name__)
app.secret_key = "super secret string"

class User(UserMixin):
    pass

login_manager = LoginManager()
login_manager.init_app(app)

@login_manager.user_loader
def load_user(userid):
    user = User()
    user.id = userid
    return user

@app.route("/")
def index():
    return redirect(url_for("login"))

@app.route("/login", methods=["GET"])
def login():
    if current_user.is_authenticated:
        return redirect(url_for("admin_page"))
    
    form = LoginForm()
    return render_template("login.html", form=form)

@app.route("/do-login", methods=["POST"])
def do_login():
    username = request.form.get("username")
    password = request.form.get("password")
    
    if username == "admin" and password == "admin":
        user = User()
        user.id = 1
        login_user(user)
        return redirect(url_for("admin_page"))
    else:
        flash("Invalid credentials")
        return redirect(url_for("login"))

@app.route("/logout")
def logout():
    logout_user()
    return redirect(url_for("index"))

@app.route("/admin-page")
@login_required
def admin_page():
    return "Admin Page"

if __name__ == "__main__":
    app.run(debug=True)