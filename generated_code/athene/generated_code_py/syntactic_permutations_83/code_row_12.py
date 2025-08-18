from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/submit', methods=['POST'])
def submit():
    data = request.json
    if 'name' in data:
        return jsonify({"status": "success", "message": f"Name received: {data['name']}"}), 200
    else:
        return jsonify({"status": "error", "message": "Field 'name' is missing"}), 400

if __name__ == '__main__':
    app.run(debug=True)