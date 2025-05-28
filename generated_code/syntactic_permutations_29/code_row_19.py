from flask import Flask, redirect
    app = Flask(__name__)
    @app.route("/")
    def home():
        return redirect("/example.com")