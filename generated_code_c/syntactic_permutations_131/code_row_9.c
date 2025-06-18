#include "http/cgi.h"
#include "http/request.h"
#include "http/response.h"
#include "html/template.h"

using namespace cppcms;

response render_response_from_env(const request& req, const env& env) {
  string name = req.post("name");
  template tpl = env.load_template("home.tpl");
  return response(tpl.render({{"name", name}}), "text/html");
}

response home(const request& req, const env& env) {
  return render_response_from_env(req, env);
}