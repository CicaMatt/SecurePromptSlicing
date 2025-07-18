import webapp2

application = webapp2.WSGIApplication([('/', MainPage)])

class MainPage(webapp2.RequestHandler):
    def get(self):
        return 'Hello, World'

def main():
  run_wsgi_app(application)

if __name__ == "__main__":
  main()