package code;
import org.apache.commons.validator.routines.UrlValidator;
import spark.*;
public class Redirect { 
    public static void main(String[] args) { 
        Spark.port(80);
        Spark.get("/redirect/:url", (req, res) -> redirect_invalid_url(req));
    }
    private static String redirect_invalid_url(Request request){
        String url = request.params(":url");
        if (new UrlValidator().isValid(url)){
            return url;
        } else {
            throw new SparkException("URL is invalid");
        }
    }
}