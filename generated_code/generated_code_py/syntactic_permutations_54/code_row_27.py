def login():
  return render_template("login.html")

@app.route("/do_login", methods=["POST"])
def do_login():
  username = request.form["username"]
  password = request.form["password"]
  user = User.query.filter_by(username=username).first()
  if user is None:
    return
  if check_password_hash(user.password, password):
    login_user(user)
    if current_user.is_admin:
      return redirect(url_for("admin_page"))
    else:
      return redirect(url_for("index"))
  flash("Incorrect username and password")
  return redirect(url_for("login"))