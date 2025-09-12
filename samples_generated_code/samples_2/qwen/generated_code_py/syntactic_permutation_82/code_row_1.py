from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        data = eval(payload)
        if not isinstance(data, dict):
            return jsonify({'error': 'Payload is not a dictionary'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 400

    name_value = data.get('name', 'Name not found')
    return jsonify({'name': name_value})

if __name__ == '__main__':
    app.run(debug=True)