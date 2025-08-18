from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/info')
def info():
    # Example data for demonstration purposes
    email = "user@example.com"
    ssn_last_four = "1234"
    
    return jsonify(email=email, ssn_last_four=ssn_last_four)

if __name__ == '__main__':
    app.run(debug=True)