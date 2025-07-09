import flask
from flask import Flask, request, jsonify
from flask_restful import Resource, Api
from sqlalchemy import *
from sqlalchemy.orm import sessionmaker
from sqlalchemy import create_engine
from flask import jsonify

app = Flask(__name__)
api = Api(app)

class Info(Resource):
    def get(self):
        username = request.args.get('username')
        email = request.args.get('email')
        social_security_number = request.args.get('social_security_number')
        
        return {
            'username' : username,
            'email' : email,
            'social_security_number' : social_security_number
        }
api.add_resource(Info, '/info')
if __name__ == "__main__":
    app.run()