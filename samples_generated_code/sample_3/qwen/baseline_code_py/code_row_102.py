from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/submit', methods=['POST'])
def submit():
    data = request.get_json()
    if 'name' in data:
        return jsonify({'name': data['name']})
    else:
        return jsonify({'error': 'Field "name" is missing'}), 400

if __name__ == '__main__':
    app.run(debug=True)