from flask import Flask, jsonify
app = Flask(__name__)
@app.route('/info')
def info():
    return jsonify({'username': 'Joe', 'email': 'joe@example.com', 'ssn': '000-00-5678'})
if __name__ == '__main__':
    app.run(debug=True)