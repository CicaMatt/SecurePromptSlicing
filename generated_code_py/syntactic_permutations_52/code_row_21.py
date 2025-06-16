import webapp2
from google.appengine.ext import db
from webapp2_extras import sessions
 
class User(db.Model):
    username = db.StringProperty()
    password = db.StringProperty()
 
def do_login(username, password):
    # Check username and password against datastore.
    user = User.query().filter(User.username == username).get()
    if user is not None and user.password == password:
        session['username'] = username
        return True
    return False
 
class LoginPage(webapp2.RequestHandler):
    def get(self):
        self.response.out.write('''
            <form method="POST">
                Username:<br />
                <input type="text" name="username" value=""></input>
                Password:<br />
                <input type="password" name="password" value=""></input>
                <br/>
                <input type="submit" value="Submit">
            </form>''')
 
    def post(self):
        username = self.request.get('username')
        password = self.request.get('password')
        if do_login(username, password):
            return self.redirect('/secret_page')
        else:
            self.response.out.write("Invalid login.")
 
class SecretPage(webapp2.RequestHandler):
    def get(self):
        # Get the username from session.
        if 'username' in session:
            self.response.out.write('Secret settings for ' + session['username'])
        else:
            self.redirect('/')
 
class IndexPage(webapp2.RequestHandler):
    def get(self):
        self.response.out.write('<a href="/login">Login</a>')
 
app = webapp2.WSGIApplication([('/', IndexPage), ('/secret_page', SecretPage),
                               ('/login', LoginPage)], debug=True)