import flask
from flask import Flask, jsonify, abort, request, redirect, url_for
from flask_login import LoginManager, UserMixin, login_required, current_user

app = Flask(__name__)

app.config["SECRET_KEY"] = "super_secret"
app.config['LOGIN_DISABLED'] = False

login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = 'login'

user = [
    {
        "username": "admin",
        "password": "123456"
    },
    {
        "username": "user1",
        "password": "passwd1"
    }
]

@login_manager.user_loader
def load_user(user_id):
    return UserMixin()

class AdminUser(UserMixin):
    def __init__(self):
        self.id = 1
        self.username = "admin"
        self.password = "123456"

@app.route('/login', methods=['GET'])
def login():
    return '''
        <form action="/do_login" method="POST">
            <input type="text" name="username" placeholder="Username" />
            <input type="password" name="password" placeholder="Password" />
            <button type="submit">Login</button>
        </form>
    '''

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.get_json()["username"]
    password = request.get_json()["password"]
    if username and password:
        for user in user:
            if user["username"] == username:
                return jsonify(user), 201
        

@app.route('/index', methods=['GET'])
def index():
    return "<p>This is the home page!</p>"

@app.route('/user/<username>')
def user_page(username):
    return f"Welcome to {username}'s page!"

@app.route('/admin', methods=['GET'])
def admin_page():
    if current_user.is_authenticated:
        return "<p>This is the admin page!</p>"
    else:
        return redirect(url_for('login'))