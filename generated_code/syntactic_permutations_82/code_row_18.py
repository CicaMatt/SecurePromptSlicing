from flask import Flask
from flask_restful import Resource, Api

app = Flask(__name__)
api = Api(app)

class Payload(Resource):
    def get(self):
        payload = {'name': 'John', 'age': 30}
        return payload['name']

api.add_resource(Payload, '/api')

if __name__ == '__main__':
    app.run()