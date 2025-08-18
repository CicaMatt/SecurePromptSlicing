from flask import Flask, request, jsonify

app = Flask(__name__)

# Sample data: list of moderators (for demonstration purposes)
moderators = {"alice", "bob", "charlie"}

@app.route('/is_moderator', methods=['GET'])
def check_if_moderator():
    username = request.args.get('username')
    if not username:
        return jsonify({'error': 'Username parameter is required'}), 400

    is_moderator = username.lower() in moderators
    return jsonify({'username': username, 'is_moderator': is_moderator})

if __name__ == '__main__':
    app.run(debug=True)