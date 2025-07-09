import json
from flask import Flask, request
app = Flask(__name__)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if email in database:
        database.pop(email)
        mailing_list.remove(email)
        return 'User successfully unsubscribed.'
    else:
        return f'{email} not found in database.'

if __name__ == "__main__":
    app.run()