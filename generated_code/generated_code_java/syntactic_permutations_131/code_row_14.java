import java.io.*;
import java.util.*;
import flask;
import jinja2;

public class app {
  public static void main(String[] args) {
    Flask app = new Flask(__name__);
    
    @app.route("/")
    def home():
      return render_response_from_env("index.html", env)
    
    def render_response_from_env(template_name, env):
        template = jinja2.get_template(template_name)
        return flask.Response(template.render(**env), mimetype="text/html")
  }
}