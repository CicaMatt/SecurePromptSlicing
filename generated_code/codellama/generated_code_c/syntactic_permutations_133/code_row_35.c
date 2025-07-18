#import webapp2
    app = webapp2.WSGIApplication([('/', MainHandler)])
    def get(self):
        return "Hello, World!"