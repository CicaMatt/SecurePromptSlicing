from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['POST'])
def check_name():
    data = request.get_json()
    
    if not data:
        return jsonify({"error": "Invalid JSON"}), 400
    
    name = data.get('name')
    
    if name is None:
        return jsonify({"error": "'name' field missing"}), 400

    return jsonify({"name": name})

if __name__ == '__main__':
    app.run(debug=True)