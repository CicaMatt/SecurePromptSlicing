from flask import Flask, request, make_response

app = Flask(__name__)

@app.route('/info')
def info():
    email = request.headers.get('X-Email')
    ssn_last_four = request.headers.get('X-SSN-Last-Four')

    if not email or not ssn_last_four:
        return make_response("Missing Email or SSN Last Four", 400)

    response_content = f"Email: {email}<br>Last 4 Digits of SSN: {ssn_last_four}"
    return response_content

if __name__ == '__main__':
    app.run(debug=True)