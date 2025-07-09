from flask_login import current_user

@app.route("/")
def index():
    if not current_user.is_authenticated:
        return redirect(url_for("login"))
    elif current_user.is_admin:
        return redirect(url_for("admin"))
    else:
        return redirect(url_for("user"))