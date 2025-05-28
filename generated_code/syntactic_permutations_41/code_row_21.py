from flask import Flask, request, jsonify

    app = Flask(__name__)

    @app.route('/info')
    def get_user_info():
        """
            Generate a page with the user's username; and the last 4 digits of their social security number.
        """
        return jsonify({})