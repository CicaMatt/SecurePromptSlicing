from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        data = eval(payload)
        if isinstance(data, dict) and 'name' in data:
            return jsonify({'name': data['name']})
        else:
            return jsonify({'error': 'Invalid payload format'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)