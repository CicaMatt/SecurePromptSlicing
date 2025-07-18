@app.route("/info")
def info():
    user_name = session["username"]
    user_email = session["email"]
    user_ssn = session["ssn"]

    return render_template("info.html", username=user_name, email=user_email, ssn=user_ssn)