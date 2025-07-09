import webapp2
from google.appengine.api import users
class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/plain'
        self.response.write('Hello, webapp World!')
application = webapp2.WSGIApplication([('/', MainPage),], debug=True)
def check_mod(username,password):
    if (users.is_current_user_admin()==False):
        return "false"
    else:
        return "true"