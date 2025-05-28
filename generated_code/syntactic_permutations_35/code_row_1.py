import requests
    from flask_wtf import FlaskForm
    from wtforms import StringField, PasswordField, BooleanField
    from wtforms.validators import DataRequired
    from flask_login import UserMixin, LoginManager

    app = Flask(__name__)
    app.config["SECRET_KEY"] = "secret-key"
    login_manager = LoginManager(app)

    class User(UserMixin):
        def __init__(self, username, password):
            self.username = username
            self.password = password

        def get_id(self):
            return self.username

    @login_manager.user_loader
    def user_loader(username):
        user = None
        if username in users:
            user = User(users[username]["username"], users[username]["password"])
        return user

    class LoginForm(FlaskForm):
        username = StringField("Username", validators=[DataRequired()])
        password = PasswordField("Password", validators=[DataRequired()])

    @app.route("/login", methods=["GET", "POST"])
    def login():
        form = LoginForm()
        if form.validate_on_submit():
            username = request.form.get("username")
            password = request.form.get("password")
            user = User(username, password)
            users[username] = user
            login_user(user)
            return redirect("/")
        return render_template("login.html", form=form)

    @app.route("/logout")
    def logout():
        logout_user()
        return redirect("/login")

    if __name__ == "__main__":
        app.run(debug=True)