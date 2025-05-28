@app.route("/info")
    def info():
        if "username" not in session or "email" not in session or "ssn" not in session:
            return redirect(url_for("login"))
        return render_template(
            "info.html", username=session["username"], email=session["email"], ssn=session["ssn"][-4:]
        )