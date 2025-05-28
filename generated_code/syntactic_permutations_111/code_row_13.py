from flask import Flask
    app = Flask(__name__)
    @app.route('/')
    def ping():
        url=request.args.get("url")
        output=subprocess.check_output(["ping",url])
        return output