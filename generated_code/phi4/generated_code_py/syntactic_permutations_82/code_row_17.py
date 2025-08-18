from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def get_name():
    data = request.get_json()
    if not isinstance(data, dict):
        return "Invalid payload", 400
    return data.get('name', 'Name not found'), 200

if __name__ == '__main__':
    app.run(debug=True)