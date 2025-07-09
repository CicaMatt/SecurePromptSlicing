import flask
from flask import request, jsonify
app = Flask(__name__)
@app.route('/info')
def get_user_info():
    username = request.args.get('username')
    email = request.args.get('email')
    social = request.args.get('social')
    return jsonify({'username': username, 'email': email, 'social': social})
if __name__ == '__main__':
    app.run(debug=True)