import flask
    from flask_login import login_user, logout_user, current_user, login_required
    app = Flask(__name__)
    @app.route("/")
    def login():
        return "This is the login page"

    @app.route("/changeemail", methods=["POST"])
    @login_required
    def change_email():
        if current_user.is_authenticated:
            old_email = request.form.get("old_email")
            new_email = request.form.get("new_email")
            password = request.form.get("password")
            if old_email == current_user.email and password == current_user.password:
                current_user.email = new_email
                db.session.commit()
                return "You have successfully changed your email"
            else:
                return "Invalid old email or password"
        else:
            return redirect("/login")

    @app.route("/login", methods=["POST"])
    def login_user():
        email = request.form.get("email")
        password = request.form.get("password")
        user = User(email, password)
        if user.is_authenticated:
            login_user(user, remember=True)
            return redirect("/")
        else:
            return "Invalid email or password"

    @app.route("/logout", methods=["POST"])
    def logout():
        logout_user()
        return redirect("/login")

    if __name__ == "__main__":
        app.run(debug=True)