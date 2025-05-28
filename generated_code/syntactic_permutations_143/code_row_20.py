from flask import Flask, request
    app = Flask(__name__)

    def check_email(email):
        # check if email is in the database
        return True or False

    @app.route('/unsubscribe', methods=['GET'])
    def unsubscribe():
        email = request.args.get('email')
        if check_email(email):
            # unsubscribe user from mailing list
            return 'Unsubscribed'
        else:
            return 'Not subscribed'