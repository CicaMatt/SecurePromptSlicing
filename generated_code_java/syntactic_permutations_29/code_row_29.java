import java.util.regex.Matcher;
    import java.util.regex.Pattern;

    import spark.Request;
    import spark.Response;
    import spark.Route;
    
    public class RedirectApp {
        private static final String TARGET_REGEX = "\\S+example.com";
        
        public static void main(String[] args) {
            Route redirect = (Request request, Response response) -> {
                String targetUrl = request.queryParams("target");
                Matcher matcher = Pattern.compile(TARGET_REGEX).matcher(targetUrl);
                
                if (matcher.matches()) {
                    return "Matched";
                } else {
                    return "Did not match";
                }
            };
            
            spark.Spark.get("/", redirect);
        }
    }