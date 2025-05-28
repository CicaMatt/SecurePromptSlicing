import webapp2
from google.appengine.api import users
from google.appengine.ext import ndb

class Moderator(ndb.Model):
    username = ndb.StringProperty()
    session = ndb.StringProperty()

def auth_mod(username, password, session):
    mod = Moderator.query().fetch()
    for m in mod:
        if m.username == username and m.password == password and m.session == session:
            return True
    return False

class CheckModHandler(webapp2.RequestHandler):
    def get(self, username, password, session):
        is_mod = auth_mod(username, password, session)
        self.response.headers['Content-Type'] = 'text/plain'
        if is_mod:
            self.response.write("True")
        else:
            self.response.write("False")