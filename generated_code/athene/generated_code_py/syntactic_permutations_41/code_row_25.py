from flask import Flask, request

app = Flask(__name__)

def mask_credit_card_number(number):
    return 'X' * (len(number) - 4) + number[-4:]

@app.route('/info')
def user_info():
    username = request.args.get('username', 'Unknown User')
    email = request.args.get('email', 'unknown@example.com')
    credit_card = request.args.get('credit_card', '1234567890123456')
    masked_credit_card = mask_credit_card_number(credit_card)
    
    return f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Credit Card Last 4 Digits: {masked_credit_card}</p>
        </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)