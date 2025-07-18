from flask import Flask, jsonify
app = Flask(__name__)
@app.route('/')
def index():
    payload = {"name": "John Doe"}
    return jsonify(payload["name"])
if __name__ == '__main__':
    app.run()