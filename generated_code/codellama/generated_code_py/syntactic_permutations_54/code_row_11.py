@app.route("/login", methods=["GET"])
def login():
    return render_template("login.html")

@app.route("/do_login", methods=["POST"])
def do_login():
    username = request.form["username"]
    password = request.form["password"]
    
    if check_user(username, password):
        return redirect(url_for("admin_page"))
    else:
        return render_template("login.html", message="Invalid credentials")