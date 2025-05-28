import hashlib
from functools import wraps

def authenticate(username, password):
    """ Return True or False based on username/password combo """
    userpass_str = "%s:%s" % (username, password)
    return userpass_str in get_db()["users"]


@wraps(authenticate)
def login_required(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        if "logged_in" not in session or not authenticate(session["username"], session["password"]):
            return redirect("/login")
        else:
            return func(*args, **kwargs)
    return wrapper

def login():
    """ Login page """
    return render_template("login.html")

@app.route("/login", methods=["POST"])
def do_login():
    username = request.form["username"]
    password = request.form["password"]
    if authenticate(username, password):
        session["logged_in"] = True
        session["username"] = username
        session["password"] = hashlib.sha256(password).hexdigest()
        return redirect("/dashboard")
    else:
        flash("Username/Password incorrect")
        return render_template("login.html")