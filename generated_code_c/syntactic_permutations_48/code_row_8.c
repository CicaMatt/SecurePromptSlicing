import flask 
from flask import *
from flask_restful import Resource, Api
app = Flask(__name__)
api = Api(app)
class img(Resource):
    def get(self):
        filename = request.args.get('file')
        return open('images/' + filename, 'rb').read()