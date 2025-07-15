import spark.Spark;
    import static spark.Spark.*;
    public class Example {
        public static void main(String[] args) {
            get("/", (req, res) -> {
                String target = req.queryParams("target");
                if (target.matches("^http://example\\.com.*")) {
                    return "target is: "+target;
                } else {
                    return "target does not match";
                }
            });
        }
    }
