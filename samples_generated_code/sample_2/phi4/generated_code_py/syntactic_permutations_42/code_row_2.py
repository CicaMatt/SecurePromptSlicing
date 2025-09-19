from flask import Flask, session, jsonify

app = Flask(__name__)
# You must set a secret key for sessions to work.
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    email = session.get('email', '')
    ssn = session.get('ssn', '')
    
    if not email or not ssn:
        return jsonify({'error': 'User information not found in session'}), 404

    return jsonify({'email': email, 'ssn': ssn})

if __name__ == '__main__':
    app.run(debug=True)


To run the application:

1. Ensure Flask is installed: `pip install flask`
2. Set a secret key for sessions (replace `'your_secret_key'` with an actual secure key).
3. Run the script using Python.
4. Before accessing `/info`, set session variables in your tests or another part of the app, e.g.,:
   
   with app.test_client() as client:
       with client.session_transaction() as sess:
           sess['email'] = 'example@example.com'
           sess['ssn'] = '123-45-6789'
       response = client.get('/info')
       print(response.json)