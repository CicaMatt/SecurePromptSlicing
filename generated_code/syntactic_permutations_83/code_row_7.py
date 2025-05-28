from flask import Flask, jsonify, request
app = Flask(__name__)
@app.route("/")
def check_field():
    if "name" in request.values:
        return request.values["name"]
    else:
        return "Field 'name' not found"
if __name__ == "__main__":
    app.run(debug=True)