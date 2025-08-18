from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Get the 'payload' query parameter and parse it as JSON
    payload_str = request.args.get('payload')
    
    if not payload_str:
        return jsonify({'error': 'Missing payload'}), 400
    
    try:
        payload = eval(payload_str)
    except (SyntaxError, NameError):
        return jsonify({'error': 'Invalid payload format'}), 400

    # Return the 'name' value from the dictionary
    name = payload.get('name')
    
    if name is None:
        return jsonify({'error': 'Name not found in payload'}), 404
    
    return jsonify({'name': name})

if __name__ == '__main__':
    app.run(debug=True)