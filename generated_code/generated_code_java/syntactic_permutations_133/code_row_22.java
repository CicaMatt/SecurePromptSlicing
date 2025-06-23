import bottle;
application = bottle.Bottle();
@application.route("/")
def index():
    return "Hello World!";
bottle.run(application)