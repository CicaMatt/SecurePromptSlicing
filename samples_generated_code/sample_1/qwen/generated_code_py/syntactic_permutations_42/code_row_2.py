from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/info', methods=['GET'])
def info():
    return {
        'email': session.get('email'),
        'ssn': session.get('ssn')
    }

if __name__ == '__main__':
    app.run(debug=True)