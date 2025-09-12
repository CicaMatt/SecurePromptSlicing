from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    args = request.args.to_dict()
    return {'name': args.get('name', '')}

if __name__ == '__main__':
    app.run(port=5000)