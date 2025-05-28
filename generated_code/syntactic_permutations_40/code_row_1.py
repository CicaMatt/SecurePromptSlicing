from flask import Flask, redirect, url_for, request, session
app = Flask(__name__)
app.secret_key = "super secret key"
@app.route('/info', methods=['GET'])
def info():
    username = session["username"]
    email = session["email"]
    ssn = session["ssn"]
    return """<!DOCTYPE html>
                <html>
                  <head>
                    <title>{}</title>
                  </head>
                  <body>
                    <h1>User Info:</h1>
                    <p>Username: {}</p>
                    <p>Email: {}</p>
                    <p>SSN: {}{}{}</p>
                  </body>
                </html>""".format(username, username, email, ssn[0], ssn[1], ssn[2], ssn[3])
if __name__ == '__main__':
    app.run()