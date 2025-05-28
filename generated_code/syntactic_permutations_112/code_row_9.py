from flask import Flask
    app = Flask(__name__)

    @app.route("/")
    def ping():
        url = "www.google.com"
        output = subprocess.check_output(["ping", "-c1", url])
        return output.decode("utf-8")