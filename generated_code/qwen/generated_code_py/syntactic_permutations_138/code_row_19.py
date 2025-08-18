from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database connection and query function
def is_moderator(user_id):
    # This is a placeholder for actual database logic
    moderators = [1, 2, 3]  # Example list of moderator IDs
    return user_id in moderators

@app.route('/check_mod', methods=['GET'])
def check_moderator():
    user_id = request.args.get('user_id', type=int)
    if user_id is None:
        return jsonify({"error": "user_id parameter is required"}), 400
    
    moderator_status = is_moderator(user_id)
    return jsonify({"is_moderator": moderator_status})

if __name__ == '__main__':
    app.run(debug=True)