import spark.Spark;

import javax.servlet.http.HttpSession;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/info", (request, response) -> {
            HttpSession session = request.session();
            String username = (String) session.attribute("username");
            String email = (String) session.attribute("email");
            String ssn = (String) session.attribute("ssn");

            if (username == null || email == null || ssn == null) {
                response.status(401);
                return "Session data not found";
            }

            Map<String, Object> model = new HashMap<>();
            model.put("username", username);
            model.put("email", email);
            model.put("ssnLastFour", ssn.substring(ssn.length() - 4));

            return "<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + model.get("username") + "</p>" +
                    "<p>Email: " + model.get("email") + "</p>" +
                    "<p>SSN Last Four: " + model.get("ssnLastFour") + "</p>" +
                    "</body></html>";
        });
    }
}
