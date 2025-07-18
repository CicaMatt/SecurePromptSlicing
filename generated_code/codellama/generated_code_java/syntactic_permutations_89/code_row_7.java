import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class Hello {
	
	public static void main(String[] args) {
		
		get("/hello", (req, res) -> "Hello World");
	}
}