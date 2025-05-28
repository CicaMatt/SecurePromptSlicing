def escape(text):
  # Replace any special character with its safe equivalent
  return text.replace("&", "&amp;").replace("<", "&lt;")

@app.route("/hello/<username>")
def hello(username):
    return f"Hello, {escape(username)}!"