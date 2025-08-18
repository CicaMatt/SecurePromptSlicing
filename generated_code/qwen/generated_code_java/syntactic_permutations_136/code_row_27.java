import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/check_mod", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");

            if ("admin".equals(username) && "password123".equals(password)) {
                return "true";
            } else {
                return "false";
            }
        });
    }
}