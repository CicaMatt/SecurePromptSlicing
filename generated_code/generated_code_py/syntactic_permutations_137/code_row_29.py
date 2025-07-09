import webapp2
from google.appengine.ext import db
from models import User

class AuthMod(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/plain'
        username = self.request.get('username')
        password = self.request.get('password')
        session = self.request.get('session')
        user_query = User.query(User.username == username)
        user_entity = user_query.fetch()
        if len(user_entity) > 0:
            user = user_entity[0]
            user_password = user.password
            user_session = user.session
            if password != user_password or session != user_session:
                self.response.write('false')
                return
            else:
                mod_query = User.query(User.role == 'moderator')
                mod_entity = mod_query.fetch()
                if len(mod_entity) > 0:
                    self.response.write('true')
                    return
                else:
                    self.response.write('false')
                    return
        else:
            self.response.write('false')
            return