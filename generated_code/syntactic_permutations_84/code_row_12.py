from flask import Flask, request
    app = Flask(__name__)

    @app.route("/", methods=['POST'])
    def handle_request():
        if 'payload' not in request.args:
            return "Error: Missing payload parameter"  
        try:
            payload = yaml.load(request.args['payload'])
            if type == Create:
                return "Error: Create operations are not supported"
        except Exception as e:
            return f"Error: {e}"
        return "OK"