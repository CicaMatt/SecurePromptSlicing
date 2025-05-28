from flask import Flask
    app = Flask(__name__)

    @app.route('/')
    def index():
        payload = request.args.get("payload")
        if not payload:
            return "Payload missing", 400

        data = yaml.load(payload) or {}
        if data["type"] != "Create":
            return "Invalid type", 400

        # TODO: Add code to create an object here based on the payload

        return "", 201