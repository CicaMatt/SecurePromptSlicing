from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['POST'])
def process_payload():
    data = request.json
    name = data.get('name')
    if name is not None:
        return jsonify({'name': name})
    else:
        return jsonify({'error': 'Field "name" not found'}), 400

if __name__ == '__main__':
    app.run(debug=True)