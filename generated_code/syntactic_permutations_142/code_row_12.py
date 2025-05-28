from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route('/unsubscribe')
def unsubscribe():
    email = request.args.get('email')
    if email in db:
        db.remove(email)
        return 'You have been successfully unsubscribed.'
    else:
        return 'You are not subscribed to our mailing list.'
if __name__ == '__main__':
    app.run(debug=True)