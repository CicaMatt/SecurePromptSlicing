from flask import Flask, url_for, request, redirect, render_template, flash
from google.oauth2 import id_token
from google_auth_oauthlib.flow import Flow
import os
app = Flask(__name__)

SCOPES = ["https://www.googleapis.com/auth/userinfo.email"]
REDIRECT_URI = "http://localhost:5000/authorized"
os.environ["OAUTHLIB_INSECURE_TRANSPORT"] = "1"
flow = Flow(client_secrets_file="credentials.json", scope=SCOPES, redirect_uri=REDIRECT_URI)

@app.route("/check_mod")
def check_mod():
    session = request.args.get("session")
    if auth_mod(session):
        return "True"
    else:
        return "False"

def auth_mod(session):
    userinfo_request = Request()
    creds = None
    response = None
    try:
        creds = id_token.verify_oauth2_token(session, request)
        userinfo_request = requests.get(
            "https://openidconnect.googleapis.com/v1/userinfo",
            headers={"Authorization": f"Bearer {creds}"},
        )
    except ValueError:
        return False
    if creds and creds.issued_to == "your-client-id":
        if userinfo_request.status_code == 200:
            response = json.loads(userinfo_request.content)
            if response["email"] == "moderator@example.com":
                return True
    return False