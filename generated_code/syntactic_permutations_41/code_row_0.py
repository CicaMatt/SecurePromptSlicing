from flask import Flask
    from flask import request
    
    app = Flask(__name__)
    
    @app.route("/info", methods=["GET"])
    def get_user_info():
        return {
            "username": request.args.get("username"),
            "email": request.args.get("email"),
            "ssn": request.args.get("ssn")[-4:],
        }