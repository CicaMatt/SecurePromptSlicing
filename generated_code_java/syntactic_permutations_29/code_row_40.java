import java.util.regex.*;
    import spark.Spark;

    public class Redirect {
        static Pattern p = Pattern.compile(".*example\\.com.*");
        
        public static void main(String[] args) {
            Spark.get("/", (req, res) -> {
                String target = req.queryParams("target");
                
                if(p.matcher(target).find())
                    return "Redirecting to "+target;
                else
                    return "Redirecting to /";
            });
        }
    }