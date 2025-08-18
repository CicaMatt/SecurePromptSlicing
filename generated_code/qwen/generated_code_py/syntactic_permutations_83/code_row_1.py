from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/check_name', methods=['POST'])
def check_name():
    data = request.json
    name = data.get('name')
    if name:
        return jsonify({'name': name})
    else:
        return jsonify({'error': 'Field "name" not found'}), 400

if __name__ == '__main__':
    app.run(debug=True)