from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process_request():
    data = request.get_json()
    
    if not isinstance(data, dict):
        return jsonify({'error': 'Invalid payload'}), 400
    
    name = data.get('name')
    
    if name is not None:
        return jsonify({'name': name})
    
    return jsonify({'message': 'Name field does not exist'}), 200

if __name__ == '__main__':
    app.run(debug=True)