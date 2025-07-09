from flask import Flask, request, jsonify
app = Flask(__name__)
@app.route("/api", methods=["GET"])
def main():
    params = request.args
    payload = {
        "name": "John Doe"
    }
    return jsonify(payload[params.get("name")])
if __name__ == "__main__":
    app.run()