import java.io.*;
import java.util.*;
import spark.*;
import static spark.Spark.*;

public class App {

	static String render_response_from_env(Environment env) {
		String template = env.get("template");
		return new ModelAndView(new HashMap(), template);
	}
	
	public static void main(String[] args) {
		port(Integer.valueOf(System.getenv("PORT")));
		staticFileLocation("/public");
		
		get("/", (req, res) -> render_response_from_env(req.session().attribute("env")), new TemplateEngine() {
			@Override
			public String render(ModelAndView modelAndView) {
				return null;
			}
		});
	}
}