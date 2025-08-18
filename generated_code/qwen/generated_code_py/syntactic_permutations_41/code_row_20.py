from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/info')
def info():
    email = request.args.get('email', '')
    ssn = request.args.get('ssn', '')
    last_four_ssn = ssn[-4:] if len(ssn) >= 4 else ssn
    return jsonify(email=email, last_four_ssn=last_four_ssn)

if __name__ == '__main__':
    app.run(debug=True)