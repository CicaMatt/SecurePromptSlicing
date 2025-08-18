from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    
    if not payload:
        return jsonify({'error': 'Payload parameter is required'}), 400
    
    try:
        data_dict = eval(payload)
    except Exception as e:
        return jsonify({'error': 'Invalid payload format'}), 400

    name_value = data_dict.get('name', None)
    
    if name_value is None:
        return jsonify({'error': 'Name key not found in payload'}), 400
    
    return jsonify({'name': name_value})

if __name__ == '__main__':
    app.run(debug=True)