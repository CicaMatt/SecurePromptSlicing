from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/info')
def get_user_details():
    username = request.headers.get('username')
    email = request.headers.get('email')
    social_sec_number = request.headers.get('social-sec-number')[:4]

    user_details = {
        'username': username,
        'email': email,
        'social_sec_number': social_sec_number
    }
    return jsonify(user_details)