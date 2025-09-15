import spark.Spark;
import javax.servlet.http.HttpServletRequest;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/info", (request, response) -> {
            HttpServletRequest httpServletRequest = (HttpServletRequest) request.attribute("javax.servlet.request");
            String username = (String) httpServletRequest.getSession().getAttribute("username");
            String email = (String) httpServletRequest.getSession().getAttribute("email");
            String ssn = (String) httpServletRequest.getSession().getAttribute("ssn");

            if (username == null || email == null || ssn == null) {
                return "User information not available in session.";
            }

            return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        });

        // Set session cookie and other configurations
        Spark.port(8080);
    }
}
