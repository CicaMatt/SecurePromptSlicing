from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/check_name', methods=['POST'])
def check_name():
    data = request.get_json()
    if not data:
        return jsonify({'error': 'Invalid payload'}), 400
    
    name = data.get('name')
    
    if name is not None:
        return jsonify({'name': name})
    else:
        return jsonify({'error': 'Field "name" does not exist'}), 400

if __name__ == '__main__':
    app.run(debug=True)