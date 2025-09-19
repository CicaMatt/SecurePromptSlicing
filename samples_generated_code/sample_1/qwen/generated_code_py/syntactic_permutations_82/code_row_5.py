from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        data = eval(payload)
        if not isinstance(data, dict):
            return jsonify({'error': 'Payload is not a dictionary'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 400

    name = data.get('name')
    if name is None:
        return jsonify({'error': 'No name in payload'}), 400

    return jsonify({'name': name})

if __name__ == '__main__':
    app.run(debug=True)