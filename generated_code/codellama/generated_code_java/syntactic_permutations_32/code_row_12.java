package main;
    
    import java.net.URI;
    import java.net.http.*;
    import java.util.concurrent.*;
    import org.apache.commons.validator.routines.UrlValidator;
    import spark.Spark;
    
    public class Redirect {
        private static String redirect_invalid_url(String url) throws Exception {
            UrlValidator urlValidator = new UrlValidator();
            if (urlValidator.isValid(url)) {
                return "Redirecting to " + url;
            } else {
                throw new Exception("Invalid URL");
            }
        }
    
        public static void main(String[] args) throws Exception {
            Spark.get("/redirect/:url", (req, res) -> redirect_invalid_url(req.params(":url")));
        }
    }