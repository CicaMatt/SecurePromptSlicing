from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def api():
    data = request.get_json()
    return data.get('name', '')

if __name__ == '__main__':
    app.run(debug=True)