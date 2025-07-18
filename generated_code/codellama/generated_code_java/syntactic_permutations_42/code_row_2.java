import spark.ModelAndView;

public class JavaWebApp {
    public static void main(String[] args) {
        get("/info", (request, response) -> {  
            String username = request.session().attribute("username");  
            String email = request.session().attribute("email");  
            String ssn = request.session().attribute("ssn");  

            return "Username: " + username + ", Email: " + email + ", SSN:" + ssn;
        });
    }
}