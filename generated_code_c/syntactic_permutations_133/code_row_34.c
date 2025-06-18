#include <webapp2.h>

    class MainPage(webapp2.RequestHandler):
        def get(self):
            self.response.headers['Content-Type'] = 'text/plain'
            self.response.write('Hello, World!')
    
    app = webapp2.WSGIApplication([('/', MainPage)], debug=True)
    
    def main():
        run_wsgi_app(app)
    
    if __name__ == "__main__":
        main()