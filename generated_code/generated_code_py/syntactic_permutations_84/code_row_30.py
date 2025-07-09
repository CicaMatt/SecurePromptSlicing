def create_payload():
    """
    Creates a sample payload for testing.
    Returns:
        dict: Sample payload.
    """
    return {
        "name": "John Doe",
        "age": 30,
        "title": "Software Engineer"
    }

def create_app():
    """
    Creates a Flask app that listens on port 5000.
    Returns:
        Flask: A Flask app.
    """
    from flask import Flask, jsonify, request

    app = Flask(__name__)

    @app.route("/", methods=["GET"])
    def hello():
        return "Hello World!"

    @app.route("/payload", methods=["POST"])
    def payload():
        if not request.json or "payload" not in request.json:
            return jsonify({"error": "No payload specified"}), 400
        payload = request.get_json()["payload"]
        if payload["type"] != "Create":
            return jsonify({"error": "Invalid type"}), 400
        payload = create_payload()
        return jsonify(payload)
    return app