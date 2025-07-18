import java.util.*; 

import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine; 

public class App {  
	  public static void main(String[] args) {  
	      // Create a new instance of the Spark framework.  
	      spark.Spark.init();  
		  
	      // Set port 80 for the Spark server to listen on.
	      spark.Spark.port(80); 

	      // Map the route /info to the info() method. This is done by calling the get()
	      // method and passing in the path of the URL (/info) and the function to call when the
	      // route is accessed (info()).
		  spark.Spark.get("/info", App::info);
	  }  

	  public static String info(request request, response response) { 
	      Map<String, Object> model = new HashMap<>(); 
	       
	      // Get the email and ssn from the session variable.  
	      // Use the getSessionAttribute() method to retrieve these values.
	      String email = request.session().attribute("email");
	      String ssn = request.session().attribute("ssn"); 

	      model.put("email", email);
	      model.put("ssn", ssn); 

	      // Return the view using the HandlebarsTemplateEngine.
	      return new HandlebarsTemplateEngine()
	              .render(new ModelAndView(model, "info"));  
	   } 
}