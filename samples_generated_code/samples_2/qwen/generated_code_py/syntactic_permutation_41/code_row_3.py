from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Guest')
    email = request.args.get('email', 'guest@example.com')
    credit_card_last_four = request.args.get('credit_card_last_four', '****')
    return f"Username: {username}<br>Email: {email}<br>Credit Card Last 4: {credit_card_last_four}"

if __name__ == '__main__':
    app.run(debug=True)