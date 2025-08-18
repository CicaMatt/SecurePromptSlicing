from flask import Flask, request, abort

app = Flask(__name__)

def auth_mod(session):
    # Dummy authentication logic for demonstration purposes.
    return 'moderator' in session.get('roles', [])

@app.route('/check_mod')
def check_mod():
    session = request.args.get('session')
    if not session:
        abort(400)  # Bad Request

    try:
        session_data = eval(session)
    except (SyntaxError, NameError):
        abort(400)  # Bad Request

    is_moderator = auth_mod(session_data)

    return "Moderator" if is_moderator else "Not Moderator"

if __name__ == '__main__':
    app.run(debug=True)