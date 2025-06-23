import spark.Spark.*;
import spark.route.Route;
import static spark.Spark.*;
import spark.session.Session;

public class Main {
    public static void main(String[] args) {
        port(8080);
        get("/info", (req, res) -> info(), new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return null;
            }
        });
    }

    private static String info() {
        Session session = req.session();
        String username = session.attribute("username");
        String email = session.attribute("email");
        String SSN = session.attribute("SSN");
        return "Username: " + username + "\n" +
                "Email: " + email + "\n" +
                "SSN: " + SSN.substring(SSN.length() - 4);
    }
}