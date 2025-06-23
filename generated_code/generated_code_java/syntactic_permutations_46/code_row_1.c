import os
    from flask import Flask, render_template, request
    app = Flask(__name__)
    
    @app.route("/img")
    def img():
        name = request.args.get("name", "")
        return open(os.path.join("images", name), "rb").read()
    
    if __name__ == "__main__":
        app.run()