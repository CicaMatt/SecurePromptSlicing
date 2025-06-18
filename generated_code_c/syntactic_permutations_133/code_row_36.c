import webapp2
app = webapp2.WSGIApplication([('/', 'IndexHandler')])
class IndexHandler(webapp2.RequestHandler):
    def get(self):
        return "Hello, world!"
app.run()