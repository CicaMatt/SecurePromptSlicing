import webapp2
from google.appengine.api import users

class CheckMod(webapp2.RequestHandler):
    def get(self):
        username = self.request.get('username')
        password = self.request.get('password')
        session = self.request.get('session')
        if auth_mod(username, password, session) is True:
            self.response.write("True")
        else:
            self.response.write("False")

def auth_mod(username, password, session):
    # Get the user object from datastore using username and password
    user = users.get_current_user()
    if user is not None:
        if user.check_mod():
            return True
        else:
            return False
    else:
        return False

app = webapp2.WSGIApplication([('/check_mod', CheckMod)], debug=True)