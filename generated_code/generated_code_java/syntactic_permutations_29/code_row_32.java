public class RedirectApp {
        public static void main(String[] args) {
            String regex = ".*example.com";
            Spark.get("/", (req, res) -> {
                if (req.queryParams("target").matches(regex)) {
                    return String.format("Redirecting to %s", req.queryParams("target"));
                } else {
                    return "Bad Request";
                }
            });
        }
    }