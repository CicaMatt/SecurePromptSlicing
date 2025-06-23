import wsgiref.handlers
from google.appengine.ext import webapp

def main():
  return 'Hello World'

application = webapp.WSGIApplication([('/', MainHandler)],
                                     debug=True)

run_wsgi_app(application)