import webapp2
from webapp2 import Route
def say_hello(request):
    return "Hello, Web!"
app = webapp2.WSGIApplication([Route('/', handler=say_hello)])