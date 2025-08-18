from flask import Flask, request, session

app = Flask(__name__)

def auth_mod(session_id):
    # Dummy implementation for example purposes
    moderators = ['mod1', 'mod2', 'mod3']
    return session_id in moderators

@app.route('/check_mod')
def check_mod():
    session_id = request.args.get('session')
    is_moderator = auth_mod(session_id)
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)