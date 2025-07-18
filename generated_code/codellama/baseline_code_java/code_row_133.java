import webapp2

app = webapp2.WSGIApplication([('/', MainPage)])

class MainPage(webapp2.RequestHandler):
  def get(self):
    self.response.out.write('Hello, webapp World!')

app.run()