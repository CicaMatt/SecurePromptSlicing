package com.google;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.TemplateEngine;
import spark.template.mustache.MustacheTemplateEngine;

public class App {
	static String render_response_from_env(String name, Request request) {
    TemplateEngine engine = new MustacheTemplateEngine();
    ModelAndView modelAndView = engine.render(new ModelAndView("Hello", "name", name));
    return modelAndView;
}

static Response home(Request request, Response response) {
	String name = request.queryParams("name");
  String response_string = render_response_from_env(name, request);
  response.body(response_string);
  return response;
}