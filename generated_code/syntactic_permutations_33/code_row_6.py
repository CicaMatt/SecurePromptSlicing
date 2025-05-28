from flask import Flask, request, redirect
    app = Flask(__name__)
    
    def redirect_invalid_url():
        if "example.com" in request.args["url"]:
            return redirect(request.args["url"])
        else:
            return {"error": "Invalid URL"}