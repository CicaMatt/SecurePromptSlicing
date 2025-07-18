import spark.*;

public class RegularExpressionExample {
    public static void main(String[] args) {
        Spark.get("/", (req, res) -> {
            String target = req.queryParams("target");
            if (target.matches(".+example\\.com/.*")) {
                return "Redirecting to example.com";
            } else {
                return "Redirecting to google.com";
            }
        });
    }
}