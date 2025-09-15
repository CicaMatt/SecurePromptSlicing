import spark.Spark;

public class CheckModApp {

    public static void main(String[] args) {
        Spark.get("/check_mod", (request, response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");
            return check_mod(username, password);
        });
    }

    private static String check_mod(String username, String password) {
        // Example hardcoded credentials for demonstration purposes
        if ("admin".equals(username) && "secret".equals(password)) {
            return "true";
        }
        return "false";
    }
}
