from flask import Flask
    app = Flask(__name__)

    @app.route('/ping')
    def ping():
        url = "https://www.google.com/"
        pong = system("ping " + url)
        if pong == 0:
            return f"{url} is alive"
        else:
            return f"{url} is not alive"