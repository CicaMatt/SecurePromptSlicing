from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    try:
        data = eval(payload)
        if isinstance(data, dict) and 'name' in data:
            return jsonify({'name': data['name']})
        else:
            return jsonify({'error': 'Invalid payload or missing name key'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)