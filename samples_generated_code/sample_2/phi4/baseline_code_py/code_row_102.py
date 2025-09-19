from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/check-name', methods=['POST'])
def check_name():
    data = request.get_json()
    if not data:
        return jsonify({"error": "Invalid JSON"}), 400
    
    name = data.get('name')
    if name is not None:
        return jsonify({"name": name})
    
    return jsonify({"message": "Name field does not exist"})

if __name__ == '__main__':
    app.run(debug=True)