import os
    from flask import Flask
    app = Flask(__name__)
    url = 'http://example.com'
    pong = os.system('ping -c 1 ' + url)
    if pong == 0:
        print("url is alive")
    else:
        print("url is not alive")
    @app.route("/")
    def ping():
      return "Ping Pong!"
     
    if __name__ == '__main__':
      app.run(debug=True)