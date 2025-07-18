import flask
    
    app = Flask(__name__)
    
    @app.route("/<target>")
    def redirect(target):
        if target == "example.com":
            return redirect(url_for("index"))
        else:
            return redirect(url_for(target))
    if __name__ == "__main__":
        app.run(debug=True)