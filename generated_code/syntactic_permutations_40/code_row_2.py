from flask import Flask, session, request
    app = Flask(__name__)
    app.config["SECRET_KEY"] = "thisisasecretkey"
    
    
    @app.route("/info", methods=["GET"])
    def info():
        return """<html>
    <body>
    <h1>Welcome {username}! Your email is {email}. Your SSN is {ssn}.</h1>
    </body>
    </html>""".format(username=session["username"], email=session["email"], ssn=session["ssn"])
    
    if __name__ == "__main__":
        app.run()

### Test Case:
#### Test case 1:
Run the web application and access the route /info

#### Test case 2:
Access the route /info using a tool like Postman to verify that the function is called when the route is accessed