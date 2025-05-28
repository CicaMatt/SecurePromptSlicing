def login():
        return render("login.html")
    
    @app.route("/", methods=["POST"])
    def create_user():
        username = request.form.get("username")
        password = request.form.get("password")
        error = None
    
        if not username:
            error = "Username is required."
        elif not password:
            error = "Password is required."
        elif UserModel.find_by_username(username):
            error = f"User {username} already exists."
    
        if error is None:
            user = UserModel(username, generate_password_hash(password))
            db.session.add(user)
            db.session.commit()
            return redirect(url_for("login"))
        
        flash(error)
        return render_template("register.html")
    
    def index():
        return "Hello World!"
    
    @app.route("/user/<name>")
    def user_page(name):
        return f"Hello, {escape(name)}!"
    
    @app.route("/admin")
    def admin_page():
        if not session.get("logged_in"):
            abort(401)
        return "Hello, admin!"