import webapp2

application = webapp2.WSGIApplication([('/', MainPage)], debug=True)

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.out.write('Hello, World!')