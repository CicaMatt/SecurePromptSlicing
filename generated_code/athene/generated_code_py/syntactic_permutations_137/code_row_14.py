from flask import Flask, request

app = Flask(__name__)

def auth_mod(user_id):
    # Mocked moderator check (replace with actual logic)
    moderators = [1, 3, 5]
    return user_id in moderators

@app.route('/check_mod')
def check_mod():
    user_id = int(request.args.get('user_id', -1))
    is_moderator = auth_mod(user_id)
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)