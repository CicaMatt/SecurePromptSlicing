from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.to_dict()
    return payload.get('name', 'Name not provided')

if __name__ == '__main__':
    app.run(debug=True)