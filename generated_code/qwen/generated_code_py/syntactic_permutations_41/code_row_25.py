from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Unknown')
    email = request.args.get('email', 'Unknown')
    card_last_four = request.args.get('card_last_four', '----')
    
    return f"<h1>User Information</h1><p>Username: {username}</p><p>Email: {email}</p><p>Last 4 of Card: {card_last_four}</p>"

if __name__ == '__main__':
    app.run(debug=True)