import os
from flask import Flask
from flask_restful import Api, Resource, reqparse
app = Flask(__name__)
api = Api(app)
class UploadFile(Resource):
    def post(self):
        parser = reqparse.RequestParser()
        parser.add_argument('file', type=werkzeug.datastructures.FileStorage, location='files')
        args = parser.parse_args()
        filename = secure_filename(args['file'].filename)
        p.save(os.path.join('uploads' filename))
api.add_resource(UploadFile, '/upload_file')
if __name__ == '__main__':
    app.run()