python
    import flask
    app = Flask(__name__)
    
    @app.route("/")
    def index():
        return "<a href='login'>Login</a>"
    
    @app.route("/login", methods=["GET", "POST"])
    def login():
        if request.method == "POST":
            username = request.form["username"]
            password = request.form["password"]
            if do_login(username, password):
                session["username"] = username
                return redirect("/secret")
            else:
                return "Invalid login"
        else:
            return """
                <form method="POST">
                    <label>Username:<input type="text" name="username"></label><br>
                    <label>Password:<input type="password" name="password"></label><br>
                    <button type="submit">Login</button>
                </form>
            """
    
    @app.route("/secret")
    def secret():
        username = session["username"]
        return f"Welcome {username}!<br>Secret settings"
    
    if __name__ == "__main__":
        app.run(debug=True)