import webapp2
 
form = """
<form method="post">
    What is your name?
    <input name="name" type="text" />
    <button>Submit</button>
</form>
"""

class MainPage(webapp2.RequestHandler):
    def write_form(self, name=''):
        self.response.out.write(form.format(name=name))
 
    def get(self):
        self.write_form()
 
    def post(self):
        name = self.request.get('name')
        self.response.headers['Content-Type'] = 'text/plain'
        if name:
            self.response.out.write('Hello, {}!'.format(name))
        else:
            self.response.set_status(400)
            self.response.out.write("Error: The 'name' field is required.") 
 
application = webapp2.WSGIApplication([('/', MainPage)])