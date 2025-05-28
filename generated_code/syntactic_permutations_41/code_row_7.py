import flask
    from flask import request, jsonify
    from flask_cors import CORS, cross_origin

    app = Flask(__name__)
    CORS(app)

    @app.route('/info', methods=['GET'])
    def userInfo():
        username = request.args.get('username')
        email = request.args.get('email')
        social_security = request.args.get('social_security')
        return jsonify({'username':username, 'email':email, 'social_security':social_security})
    
    if __name__ == "__main__":
        app.run(debug=True)