import os

os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'

from requests_oauthlib import OAuth2Session
from flask import Flask, request, redirect, session, url_for

app = Flask(__name__)

# This information is obtained upon registration of the application on Google APIs
client_id = json.loads(
    open('client_secrets.json', 'r').read())['web']['client_id']
client_secret = json.loads(
    open('client_secrets.json', 'r').read())['web']['client_secret']

oauth = OAuth2Session(client_id, redirect_uri='http://localhost:5000/login/authorized', scope=['profile', 'email'])

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login')
def login():
    authorization_url, state = oauth.authorization_url(
        'https://accounts.google.com/o/oauth2/auth',
        access_type='offline',
        prompt='select_account'
    )
    session['oauth_state'] = state
    return redirect(authorization_url)

@app.route('/login/authorized')
def authorized():
    # Redirect user to home page if already logged in.
    if 'profile' in session:
        return redirect(url_for('index'))
    if 'error' not in request.args:
        if 'code' not in request.args:
            return render_template('login.html', error="No code received from Google")
        else:
            try:
                token = oauth.fetch_token(
                    'https://accounts.google.com/o/oauth2/token',
                    client_secret=client_secret,
                    authorization_response=request.url)
            except ValueError as e:
                return render_template('login.html', error="Invalid code received from Google")
            # At this point the user has granted access to our app and a token 
            # has been generated which can be used for authentication to Google APIs
            session['oauth_token'] = token

            # Request user profile information from Google
            google = get_google_service(
                'oauth2', 'v1', credentials=oauth)
            profile = google.userinfo().get().execute()
            session['profile'] = {
                'name': profile.get('name'),
                'email': profile.get('email')
            }
            return redirect(url_for('index'))
    else:
        return render_template('login.html', error=request.args.get('error'))

@app.route('/logout')
def logout():
    # Remove session data related to the user
    session.pop('profile', None)
    session.pop('oauth_token', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)