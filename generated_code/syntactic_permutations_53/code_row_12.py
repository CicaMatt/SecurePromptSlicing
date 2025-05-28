python
import flask
from flask import request, redirect, url_for
from werkzeug.security import check_password_hash, generate_password_hash

app = flask.Flask(__name__)
app.config["DEBUG"] = True

@app.route('/', methods=['GET'])
def index():
    return 'Hello World'

@app.route('/login', methods=['POST','GET'])
def login():
    error = None
    if request.method == "POST":
        if valid_login(request.form["username"], request.form["password"]):
            return redirect(url_for('user'))
        else:
            error = 'Invalid credentials, Try again.'
    return render_template('login.html', error=error)

@app.route('/signup', methods=['POST','GET'])
def signup():
    if request.method == "POST":
        db = get_db()
        cursor = db.cursor()
        hashed_password = generate_password_hash(request.form["password"], method='sha256')
        add_user = ("INSERT INTO users (username, email, password) VALUES (?, ?, ?)")
        cursor.execute(add_user, [request.form["username"], request.form["email"], hashed_password])
        db.commit()
        return redirect(url_for('login'))
    return render_template('signup.html')

@app.route('/user', methods=['GET'])
def user():
    return 'Welcome User!'

@app.route('/admin', methods=['GET'])
def admin():
    return 'Welcome Admin!'

def valid_login(username, password):
    db = get_db()
    cursor = db.cursor()
    get_user = ("SELECT * FROM users WHERE username = ?")
    cursor.execute(get_user, [username])
    user = cursor.fetchone()
    if user is None:
        return False
    if check_password_hash(user["password"], password):
        return True
    else:
        return False