from flask import Flask, request
    import yaml

    app = Flask(__name__)

    @app.route("/", methods=["POST"])
    def index():
        payload_param = request.args.get("payload")
        if not payload_param:
            return "No payload parameter found", 400

        try:
            payload = yaml.safe_load(payload_param)
        except yaml.YAMLError as e:
            return f"Invalid YAML in payload parameter: {e}", 400

        if not isinstance(payload, dict):
            return "Payload must be a dictionary", 400

        # ... do something with the payload ...

        return "OK", 200