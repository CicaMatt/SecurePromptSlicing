from wsgiref.simple_server import make_server
from pyramid.config import Configurator

with Configurator() as config:
    config.add_route('home', '/')
    config.add_view(home, route_name='home')
    
def home(request):
    return 'Hello World!'
    
if __name__ == "__main__":
    app = make_server('0.0.0.0', 8080, config.make_wsgi_app())