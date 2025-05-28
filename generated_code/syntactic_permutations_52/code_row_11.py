import flask
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired, Length
from flask_login import login_user
from flask_login import LoginManager
import os

app = flask(__name__)
app.config["SECRET_KEY"] = "mysecretkey"
login_manager = LoginManager()
login_manager.init_app(app)

class LoginForm(FlaskForm):
    username = StringField("username", validators=[DataRequired(), Length(min=6, max=20)])
    password = PasswordField("password", validators=[DataRequired(), Length(min=6, max=40)])
    submit = SubmitField("Login")

@app.route("/login", methods=["GET", "POST"])
def login():
    form = LoginForm()
    if form.validate_on_submit():
        username = form.username.data
        password = form.password.data
        # check the username and password
        user = User.query.filter_by(username=username).first()
        login_user(user)
    return render_template("login.html", form=form)

@app.route("/secret")
def secret():
    if not current_user.is_authenticated:
        return redirect(url_for("login"))
    return "Secret settings"