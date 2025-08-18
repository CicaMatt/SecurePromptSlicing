import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/check_mod", (request, response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");

            if ("admin".equals(username) && "password123".equals(password)) {
                return "true";
            } else {
                return "false";
            }
        });
    }
}