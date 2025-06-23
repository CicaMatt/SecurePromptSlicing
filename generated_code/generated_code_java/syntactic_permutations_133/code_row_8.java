import webapp2

app = webapp2.WSGIApplication([('/', MainPage)])

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/plain'
        self.response.write('Hello, World!')

app.run()