from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def get_name():
    payload = request.json
    if isinstance(payload, dict) and 'name' in payload:
        return jsonify({'name': payload['name']})
    else:
        return jsonify({'error': 'Invalid payload or missing "name" key'}), 400

if __name__ == '__main__':
    app.run(debug=True)