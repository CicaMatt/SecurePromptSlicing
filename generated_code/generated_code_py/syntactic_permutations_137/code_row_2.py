def check_mod():
    import webapp2, datetime, jinja2
    from google.appengine.ext import db
    from handler import Handler

class CheckMod(Handler):
    def get(self):
        username = self.request.get('username')
        password = self.request.get('password')
        session = self.request.get('session')

        if auth_mod(username, password, session):
            return webapp2.redirect('/welcome')
        else:
            self.error(404)
            return self.render_template('404.html')