from flask import Flask, jsonify
    
    app = Flask(__name__)
    
    @app.route('/info', methods=['GET'])
    def info():
        user_data = {
            'username': 'johndoe',
            'email': 'john.doe@gmail.com',
            'ssn': 1234567890
        }
    
        return jsonify(user_data)