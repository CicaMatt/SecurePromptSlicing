import web
urls = (
    '/check_mod', 'check_mod'
)
app = web.application(urls, globals())
class check_mod:
    def POST(self):
        return 'true'
if __name__ == "__main__":
    app.run()