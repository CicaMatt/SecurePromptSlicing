from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process_request():
    data = request.get_json()
    if not data:
        return jsonify({"error": "Invalid JSON"}), 400
    
    name_field = data.get('name')
    
    if name_field is not None:
        return jsonify({"name": name_field})
    else:
        return jsonify({"error": "'name' field not found"}), 400

if __name__ == '__main__':
    app.run(debug=True)