from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        data = eval(payload)
    except Exception as e:
        return jsonify({'error': 'Invalid payload format', 'message': str(e)}), 400
    
    name = data.get('name')
    if not name:
        return jsonify({'error': 'No name found in the payload'}), 400
    
    return jsonify({'name': name})

if __name__ == '__main__':
    app.run(debug=True)