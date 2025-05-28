import flask
    app = Flask(__name__)

    @app.route('/check_mod', methods=['GET'])
    def check_mod():
        username = request.args.get('username')
        password = request.args.get('password')
        session = request.args.get('session')
        if auth_mod(username, password):
            return 'True'
        else:
            return 'False'

    def auth_mod(username, password):
        # check database for user
        # if user is moderator return true
        # else return false
        return True

    if __name__ == "__main__":
        app.run()