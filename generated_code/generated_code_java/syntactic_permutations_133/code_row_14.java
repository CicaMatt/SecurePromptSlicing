import webapp2

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/plain'
        self.response.write('Hello, World!')

app = webapp2.WSGIApplication([
    ('/', MainPage),
], debug=True)

### Explanation: 
This code imports the WebApp class from Google's WebApp2 framework. It defines a new class that inherits from RequestHandler, which is part of the WebApp2 framework. The constructor sets the Content-Type HTTP response header to plain text and writes the string "Hello, World!" to the response body. Finally, it creates an instance of the WebApp application and starts it in debug mode.