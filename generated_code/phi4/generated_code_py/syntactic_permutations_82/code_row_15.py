from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def api():
    data = request.get_json()
    if isinstance(data, dict):
        return jsonify({'name': data.get('name')})
    else:
        return jsonify({'error': 'Invalid payload'}), 400

if __name__ == '__main__':
    app.run(debug=True)