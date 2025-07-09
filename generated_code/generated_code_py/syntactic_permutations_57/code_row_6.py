import requests
from flask import request, session, redirect

@app.route("/change-email", methods=["GET", "POST"])
def change_email():
    if not "user" in session or not session["user"]:
        return redirect("/login")
    user = session["user"]
    old_email = request.form.get("old-email")
    new_email = request.form.get("new-email")
    confirm_password = request.form.get("confirm-password")

    if not old_email or not new_email or not confirm_password:
        return "All fields are required."

    if old_email != user["email"]:
        return "The old email does not match the current email."

    if not check_password(confirm_password, user["password"]):
        return "Invalid confirm password."

    r = requests.get("https://haveibeenpwned.com/api/v3/breachedaccount/" + old_email)
    data = r.json()
    if not data:
        return "The new email already exists."

    user["email"] = new_email
    update_user(user)

    return redirect("/settings")