from flask import Flask, redirect, request
    app = Flask(__name__)
    
    @app.route("/")
    def index():
        target = request.args.get("target")
        if target is None or not re.match(r".*example\.com", target):
            return redirect("/", code=302)
        else:
            return redirect(target, code=302)