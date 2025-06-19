import spark.Spark;
    import spark.Request;
    import spark.Response;
    import java.util.regex.Pattern;
    import java.util.regex.Matcher;
    
    public class Redirect {
        private static final Pattern p = Pattern.compile(".*example\\.com.*");
        
        public static void main(String[] args) {
            Spark.get("/", (req, res) -> {
                String target = req.queryParams("target");
                if (p.matcher(target).matches()) {
                    return "Redirecting to " + target;
                } else {
                    res.redirect("/");
                    return null;
                }
            });
        }
    }