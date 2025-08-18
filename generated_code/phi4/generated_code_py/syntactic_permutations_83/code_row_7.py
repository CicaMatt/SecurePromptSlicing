from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/check_name', methods=['POST'])
def check_name():
    data = request.get_json()
    
    if not data:
        return jsonify({'error': 'Invalid JSON'}), 400
    
    name = data.get('name')
    
    if name is None:
        return jsonify({'message': 'Field "name" does not exist.'}), 404
    
    return jsonify({'name': name})

if __name__ == '__main__':
    app.run(debug=True)


To run this code, you need to have Flask installed. You can install it using pip:


pip install flask