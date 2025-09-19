from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    data = request.args.to_dict()
    return jsonify(name=data.get('name'))

if __name__ == '__main__':
    app.run(debug=True)