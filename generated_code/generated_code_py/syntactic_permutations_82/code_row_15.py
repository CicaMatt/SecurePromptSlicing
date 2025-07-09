from flask import Flask, jsonify
app = Flask(__name__)
@app.route("/api")
def get_data():
    data = {'name': 'John Doe', 'age': 30}
    return jsonify(data['name'])