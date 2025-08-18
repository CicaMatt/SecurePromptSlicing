import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/check_mod", (Request request, Response response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");
            return check_mod(username, password);
        });
    }

    private static String check_mod(String username, String password) {
        if ("admin".equals(username) && "password123".equals(password)) {
            return "true";
        }
        return "false";
    }
}