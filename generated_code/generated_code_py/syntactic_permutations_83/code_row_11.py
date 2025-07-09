import flask 
from flask import request 
app = Flask(__name__) 
@app.route('/') 
def index(): 
    name = None 
    if request.json and 'name' in request.json: 
        name = request.json['name'] 
    return name