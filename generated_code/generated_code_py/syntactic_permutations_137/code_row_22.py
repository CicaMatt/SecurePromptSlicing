import webapp2
from google.appengine.api import users
from google.appengine.ext import ndb

def check_mod(username, password, session):
    return auth_mod(username, password, session)

class User(ndb.Model):
    username = ndb.StringProperty()
    email = ndb.StringProperty()
    role = ndb.StringProperty()

def auth_mod(username, password, session):
    user = users.get_current_user()
    if user:
        return True
    else:
        return False

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/plain'
        self.response.write('Hello, webapp World!')

app = webapp2.WSGIApplication([('/', MainPage)],
                              debug=True)