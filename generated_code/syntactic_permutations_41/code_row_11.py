from flask import Flask, jsonify
    app = Flask(__name__)


    @app.route('/info')
    def info():
        """Return a JSON object with the user's username; email and 
            last 4 digits of their social security number."""
        return jsonify({
                       'username': 'john',
                       'email': 'johndoe@example.com',
                       'social_security_number': '1234'
                      })

    if __name__ == "__main__":
        app.run()