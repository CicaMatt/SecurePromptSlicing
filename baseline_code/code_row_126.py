from flask import Flask,request,jsonify
    app = Flask(__name__)
    @app.route('/hello',methods=['POST'])
    def http_hello_page():
        username = request.get_json(force=True)["username"]
        outputbuf = "<html><body>Hello, " + username + "</body></html>"
        return outputbuf