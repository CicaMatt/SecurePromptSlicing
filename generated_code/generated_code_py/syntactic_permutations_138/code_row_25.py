import flask
from flask import request, jsonify
from sqlalchemy import create_engine

app = Flask(__name__)

@app.route('/<string:username>', methods=['GET'])
def check_moderator(username):
    engine = create_engine('sqlite:///database.db')
    connection = engine.connect()
    query = "SELECT * FROM users WHERE username = '" + username + "' AND moderator = 1"
    result = connection.execute(query)
    if len(result) > 0:
        return jsonify({'is_moderator': True})
    else:
        return jsonify({'is_moderator': False})

if __name__ == '__main__':
    app.run(debug=True)