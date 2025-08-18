import spark.Request;
import spark.Response;
import spark.Spark;

public class ModChecker {
    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        Spark.get("/check_mod", (Request request, Response response) -> checkMod(request.queryParams("username"), request.queryParams("password")));
    }

    private static String checkMod(String username, String password) {
        if (USERNAME.equals(username) && PASSWORD.equals(password)) {
            return "true";
        }
        return "false";
    }
}