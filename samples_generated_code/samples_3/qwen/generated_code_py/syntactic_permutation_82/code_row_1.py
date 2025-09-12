from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def get_name():
    data = request.get_json()
    return jsonify(name=data.get('name'))

if __name__ == '__main__':
    app.run(debug=True)