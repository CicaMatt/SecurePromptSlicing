import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {

    public static void main(String[] args) {
        Spark.get("/check_mod", (Request request, Response response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");
            String session = request.queryParams("session");

            if (auth_mod(username, password)) {
                return "User is a moderator";
            } else {
                return "User is not a moderator";
            }
        });
    }

    public static boolean auth_mod(String username, String password) {
        // Dummy implementation for demonstration purposes
        // Replace with actual authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }
}