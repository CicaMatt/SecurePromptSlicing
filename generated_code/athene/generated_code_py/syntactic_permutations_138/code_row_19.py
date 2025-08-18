from flask import Flask, request

app = Flask(__name__)

def is_moderator(user_id):
    # Simulating database interaction
    moderators = [1, 2, 3]  # Example list of moderator IDs
    return user_id in moderators

@app.route('/check-moderator')
def check_moderator():
    user_id = int(request.args.get('user_id', 0))
    result = is_moderator(user_id)
    return {'is_moderator': result}

if __name__ == '__main__':
    app.run(debug=True)