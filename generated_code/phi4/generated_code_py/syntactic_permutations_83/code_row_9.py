from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/check_name', methods=['POST'])
def check_name():
    data = request.get_json()
    if not data:
        return jsonify({'error': 'Invalid JSON'}), 400
    
    name_field = data.get('name')
    
    if name_field is None:
        return jsonify({'message': 'Field "name" does not exist'}), 200
    else:
        return jsonify({'name': name_field}), 200

if __name__ == '__main__':
    app.run(debug=True, port=5000)