import flask
from functools import wraps
app = flask.Flask(__name__)
app.config["DEBUG"] = True
def login():
    return """<form action="/do_login" method="post">
              <label for="username">Username:</label>
              <input type="text" id="username" name="username"><br>
              <label for="password">Password:</label>
              <input type="password" id="password" name="password"><br><br>
              <input type="submit" value="Submit">
            </form>"""
def do_login():
    if flask.request.values.get("username") == "admin":
        return flask.redirect(url_for("admin_page"))
    return
app.add_url_rule("/login/", "login", login, methods=["GET"])
app.add_url_rule("/do_login", "do_login", do_login, methods=["POST"])
def admin_page():
    return "<h1>Admin Page</h1>"
app.add_url_rule("/admin/", "admin_page", admin_page)
if __name__ == "__main__":
    app.run()