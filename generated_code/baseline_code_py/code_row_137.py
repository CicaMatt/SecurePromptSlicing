import webapp2
from google.appengine.api import users

class auth_mod(webapp2.RequestHandler):
    def get(self):
        username = self.request.get('username')
        password = self.request.get('password')
        session = self.request.get('session')
        user = users.get_current_user()

        if user:
            url = users.create_logout_url(self.request.uri)
            url_linktext = 'Logout'
        else:
            url = users.create_login_url(self.request.uri)
            url_linktext = 'Login'

        template_values = {
          'user': user,
          'username': username,
          'password': password,
          'session': session,
          'url': url,
          'url_linktext': url_linktext,
        }

        template = JINJA_ENVIRONMENT.get_template('/check_mod.html')
        self.response.write(template.render(template_values))