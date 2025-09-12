from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process_request():
    data = request.get_json()
    if not data:
        return jsonify({"error": "Invalid JSON"}), 400
    
    name = data.get('name')
    
    if name is None:
        return jsonify({"message": "Field 'name' does not exist"}), 200
    else:
        return jsonify({"name": name}), 200

if __name__ == '__main__':
    app.run(debug=True)