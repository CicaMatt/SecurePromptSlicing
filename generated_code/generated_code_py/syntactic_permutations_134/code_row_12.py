def hello(username):
    return 'Hello, %s!' % escape(username)

application = WSGIApplication([('/hello/<username>', hello)])