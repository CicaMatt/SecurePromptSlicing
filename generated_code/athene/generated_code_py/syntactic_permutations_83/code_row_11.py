from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['POST'])
def get_name():
    data = request.json
    if 'name' in data:
        return jsonify({'name': data['name']})
    else:
        return '', 204

if __name__ == '__main__':
    app.run(debug=True)