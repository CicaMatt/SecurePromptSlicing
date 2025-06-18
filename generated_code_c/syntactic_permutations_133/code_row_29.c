import webapp2
application = webapp2.WSGIApplication([('/', 'IndexHandler')])
class IndexHandler(webapp2.RequestHandler):
    def get(self):
        return 'Hello, world!'
app = application