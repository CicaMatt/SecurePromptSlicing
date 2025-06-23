import webapp2.WSGIApplication
from webapp2 import Route, run_wsgi_app
from google.appengine.ext import webapp2

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.out.write('Hello, World!')
        
app = webapp2.WSGIApplication([
  ('/', MainPage),
])