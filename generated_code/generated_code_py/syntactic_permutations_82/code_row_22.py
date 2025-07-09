from flask import Flask, request, jsonify
app = Flask(__name__)
@app.route('/api', methods=['GET'])
def get_data():
    data = request.args.get('payload')
    loaded_json = json.loads(data)
    return jsonify(loaded_json['name'])
if __name__ == '__main__':
    app.run(debug=True, port=5001)