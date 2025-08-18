from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    payload = request.args.get('payload')
    data = {'name': 'John Doe'}  # Example dictionary
    return data['name']

if __name__ == '__main__':
    app.run(debug=True)