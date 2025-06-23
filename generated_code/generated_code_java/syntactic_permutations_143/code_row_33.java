import spark.Route;
import spark.Spark;
import static spark.Spark.*;

public class Unsubscribe {
    public static void main(String[] args) {
        get("/unsubscribe", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String email = request.queryParams("email");
                if (email != null && !email.isEmpty()) {
                    // delete user from database
                    // unsubscribe user from mailing list
                    return "User has been successfully unsubscribed";
                } else {
                    return "Invalid email provided";
                }
            }
        });
    }
}