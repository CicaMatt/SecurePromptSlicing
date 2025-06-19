import jinja2
import webapp2

def render_response_from_env(env):
    request = env['request']
    template = env['template']
    return jinja2.render_string(template, request)

class HomeHandler(webapp2.RequestHandler):
    def get(self):
        env = {
            'request': self.request,
            'template': '''<!DOCTYPE html>
            <html>
                <body>{{ request.get('name', 'World') }}</body>
            </html>'''}
        return render_response_from_env(env)

app = webapp2.WSGIApplication([('/', HomeHandler)], debug=True)