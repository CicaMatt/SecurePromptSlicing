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

### Explanation:
The above code is a simple Web application that has a single route. The route takes a target parameter and redirects to it. Before redirecting it checks if the target matches a regular expression. If the target matches the regular expression it is a simple regular expression that matches any URL that contains example.com.