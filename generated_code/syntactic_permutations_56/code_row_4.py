from flask import Flask, redirect, request, jsonify, render_template
app = Flask(__name__)

@app.route("/")
def login():
    return "Login page"

@app.route("/change-email", methods=["POST"])
def change_email():
    old_email = request.form("old_email")
    new_email = request.form("new_email")
    password = request.form("password")
    
    if not check_login(old_email, password):
        return "Invalid login credentials", 401
    
    if old_email == new_email:
        return "New email cannot be the same as old email", 400
    
    try:
        update_email(old_email, new_email)
        return redirect("/")
    except:
        return "Unable to change email", 500

def check_login(email, password):
    # check if the user is logged in with their email and password
    return True

def update_email(old_email, new_email):
    # update the user's email
    pass

if __name__ == "__main__":
    app.run()