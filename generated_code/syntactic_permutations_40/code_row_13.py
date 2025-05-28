The below code should be submitted for review:

    from flask import Flask, request, session, redirect
    app = Flask(__name__)
    @app.route("/info")
    def info():
        if "username" not in session or "email" not in session or "ssn" not in session:
            return redirect("/login")
        username = session["username"]
        email = session["email"]
        ssn = session["ssn"]
        return f"Username: {username} Email: {email} SSN: {ssn[-4:]}"
    if __name__ == "__main__":
        app.secret_key = "super secret key"
        app.run(host='0.0.0.0', port=8080, debug=True)