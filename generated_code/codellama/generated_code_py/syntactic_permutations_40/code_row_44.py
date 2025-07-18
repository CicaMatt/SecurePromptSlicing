@app.route("/info")
def info():
    user = {
        "username": "testuser",
        "email": "testuser@test.com"
    }
    return render_template("info.html", user=user)