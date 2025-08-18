from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/submit', methods=['POST'])
def submit():
    data = request.json
    name = data.get('name')
    if name:
        return jsonify({'name': name})
    else:
        return jsonify({'error': 'Field "name" is required'}), 400

if __name__ == '__main__':
    app.run(debug=True)