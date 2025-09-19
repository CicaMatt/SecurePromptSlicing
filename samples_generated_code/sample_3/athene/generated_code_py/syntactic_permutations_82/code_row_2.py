from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    data = request.args.to_dict()
    return {'name': data.get('name', '')}

if __name__ == '__main__':
    app.run(debug=True)