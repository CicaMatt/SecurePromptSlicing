import os
    
    from flask import Flask, request, render_template, make_response, abort
    from flask_session import Session
    from tempfile import mkdtemp
    
    app = Flask(__name__)
    app.config["SESSION_FILE_DIR"] = mkdtemp()
    app.config["SESSION_PERMANENT"] = False
    Session(app)
    
    @app.route("/")
    def login():
        return render_template("login.html")
    
    @app.route("/session", methods=['POST'])
    def session():
        if request.form["username"] == "admin" and request.form["password"] == "admin":
            return make_response(render_template("session.html"))
        else:
            abort(401)