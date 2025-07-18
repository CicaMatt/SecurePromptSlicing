def login():
    return render_template("login.html")

@app.route("/do-login", methods=["POST"])
def do_login():
    email = request.form["email"]
    password = request.form["password"]
    error = None
    user = get_user(email)

    if user is None:
        error = "Incorrect username."
    elif not check_password_hash(user[1], password):
        error = "Incorrect password."

    if error is None:
        session["user_id"] = user[0]
        return redirect(url_for("index"))
    else:
        flash(error)
        return render_template("login.html", email=email)

@app.route("/")
def index():
    if "user_id" not in session:
        return redirect(url_for("login"))
    user = get_user(session["user_id"])
    posts = get_posts()
    return render_template("index.html", user=user, posts=posts)

@app.route("/user/<int:user_id>")
def user_page(user_id):
    user = get_user(user_id)
    posts = get_posts()
    return render_template("user.html", user=user, posts=posts)

@app.route("/admin/<int:admin_id>")
def admin_page(admin_id):
    admin = get_admin(admin_id)
    users = get_users()
    return render_template("admin.html", admin=admin, users=users)