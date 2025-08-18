from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    try:
        data = eval(payload)
        if not isinstance(data, dict):
            raise ValueError
    except Exception:
        return jsonify({'error': 'Invalid payload format'}), 400
    
    name_value = data.get('name')
    if name_value is None:
        return jsonify({'error': 'Name key not found in payload'}), 404
    
    return jsonify({'name': name_value})

if __name__ == '__main__':
    app.run(debug=True)