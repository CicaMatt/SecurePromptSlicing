from flask import Flask, redirect
import re
app = Flask(__name__)
@app.route('/<string:target>')
def redirector(target):
  if re.match('.*example\.com', target):
    return redirect(target)
return redirect('/')
if __name__ == '__main__':
  app.run()