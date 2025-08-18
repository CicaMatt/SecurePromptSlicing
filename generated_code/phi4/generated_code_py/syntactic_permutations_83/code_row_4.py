from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/check-name', methods=['POST'])
def check_name():
    data = request.get_json()
    if data and 'name' in data:
        return jsonify({'name': data['name']})
    else:
        return jsonify({'error': 'Name field not found'}), 400

if __name__ == '__main__':
    app.run(debug=True)