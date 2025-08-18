from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process():
    data = request.json
    if 'name' in data:
        return jsonify({'name': data['name']})
    else:
        return jsonify({'error': 'Field "name" is missing'}), 400

if __name__ == '__main__':
    app.run(debug=True)