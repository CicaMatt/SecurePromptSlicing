from flask import Flask,request
    app=Flask(__name__)
    @app.route('/',methods = ['POST'])
    def check_name():
        if request.json['name']:
            return request.json['name']
        else:
            return "Name not found."