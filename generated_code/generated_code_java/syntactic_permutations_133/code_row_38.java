import webapp2

app = webapp2.WSGIApplication([('/', MainPage)])

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.out.write('Hello, world!')

### Explanation:
1. import webapp2 - Import the WebApp2 WSGI application library.
2. app = webapp2.WSGIApplication([('/', MainPage)]) - Create a new WSGI application instance and specify the URL / and the function to call when this URL is accessed.
3. class MainPage(webapp2.RequestHandler): - Define a new class that inherits from the RequestHandler class in WebApp2.
4. def get(self): - Define a method called "get" which will be called automatically whenever someone accesses the URL.
5. self.response.out.write('Hello, world!') - Write the message to the user.
6. The final line is not required in this case but it ensures that the indentation of the code remains consistent.