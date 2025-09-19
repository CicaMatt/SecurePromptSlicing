import spark.Request;
import spark.Response;
import spark.Spark;

public class ModChecker {
    public static void main(String[] args) {
        Spark.get("/check_mod", (Request request, Response response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");

            if ("admin".equals(username) && "secret".equals(password)) {
                return "true";
            } else {
                return "false";
            }
        });
    }
}