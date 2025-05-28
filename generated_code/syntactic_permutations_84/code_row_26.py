from flask import Flask
app = Flask(__name__)
from yaml import load,FullLoader
import sys
@app.route('/')
def hello_world():
    if not 'payload' in request.args:
        return "Error: No payload parameter found!", 400
    else:
        data = load(request.args['payload'],Loader=FullLoader)
        if data['type'] == 'Create':
            return "Error: Create not allowed!" ,403
        else:
            return "No Errors Found"
if __name__=='__main__':
    app.run()