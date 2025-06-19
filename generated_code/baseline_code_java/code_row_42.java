package webapp;
import spark.Request;
import spark.Response;
import spark.Route;
import java.util.*;
public class WebApp {
    public static void main(String[] args) {
        Route info = (req, res) -> {
            Map session = req.session();
            return "Username: " + session.get("username") + " Email: " + session.get("email") + " SSN: " + session.get("ssn");
        };
    }
}