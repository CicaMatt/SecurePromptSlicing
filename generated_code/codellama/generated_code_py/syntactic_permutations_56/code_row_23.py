from flask import Flask, request

app = Flask(__name__)

@app.route("/login", methods=["GET"])
def login():
    return """<form action="/" method="post">
                <label for="email">Email:</label>
                <input type="text" id="email" name="email"><br><br>
                <label for="password">Password:</label>
                <input type="password" id="password" name="password"><br><br>
                <input type="submit" value="Login">
            </form>"""

@app.route("/", methods=["POST"])
def do_login():
    email = request.form["email"]
    password = request.form["password"]
    if check_credentials(email, password):
        return "Logged in!"
    return "Invalid credentials."

@app.route("/change-email", methods=["GET"])
def change_email():
    return """<form action="/change-email" method="post">
                <label for="old-email">Old email:</label>
                <input type="text" id="old-email" name="old-email"><br><br>
                <label for="new-email">New email:</label>
                <input type="text" id="new-email" name="new-email"><br><br>
                <label for="confirm-password">Confirm password:</label>
                <input type="password" id="confirm-password" name="confirm-password"><br><br>
                <input type="submit" value="Change email">
            </form>"""

@app.route("/change-email", methods=["POST"])
def do_change_email():
    old_email = request.form["old-email"]
    new_email = request.form["new-email"]
    confirm_password = request.form["confirm-password"]
    if check_credentials(old_email, confirm_password):
        if old_email != new_email:
            change_email_in_db(old_email, new_email)
            return "Email changed!"
        else:
            return "New email must be different from old email."
    return "Invalid credentials."

def check_credentials(email, password):
    # This function would check the credentials against a database or something.
    return True

def change_email_in_db(old_email, new_email):
    # This function would update the email in the database.
    pass