#import webapp2
webapp2 = webapp2.WSGIApplication([('/', 'IndexHandler')], debug=True)
class IndexHandler(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/plain'
        self.response.out.write('Hello, World!')
application = app
if __name__ == '__main__':
   app.run()