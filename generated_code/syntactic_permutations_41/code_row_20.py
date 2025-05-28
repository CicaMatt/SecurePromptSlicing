from flask import Flask, jsonify

    app = Flask(__name__)

    @app.route('/info', methods=['GET'])
    def info():
        return jsonify({'username': 'test', 'email': 'test@example.com', 'social_security_number': '1234'}), 200