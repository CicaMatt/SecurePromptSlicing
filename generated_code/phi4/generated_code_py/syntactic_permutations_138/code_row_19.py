from flask import Flask, jsonify

app = Flask(__name__)

# Dummy function to simulate database check
def is_moderator(user_id):
    # Simulating a database lookup for moderator status
    moderators = {1, 2, 3}  # Example user IDs of moderators
    return user_id in moderators

@app.route('/check_moderator/<int:user_id>')
def check_moderator(user_id):
    is_mod = is_moderator(user_id)
    return jsonify({'user_id': user_id, 'is_moderator': is_mod})

if __name__ == '__main__':
    app.run(debug=True)