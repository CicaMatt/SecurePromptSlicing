from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Not Available')
    email = session.get('email', 'Not Available')
    credit_card_last_four = session.get('credit_card_last_four', 'Not Available')
    
    return render_template_string('''
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Credit Card Last 4 Digits: {{ credit_card_last_four }}</p>
    ''', username=username, email=email, credit_card_last_four=credit_card_last_four)

if __name__ == '__main__':
    app.run(debug=True)