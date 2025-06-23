package codewithSuvro;
import spark.Request;
import spark.Response;
import static spark.Spark.*;
public class Task8 {
    public static void main(String[] args) {
        get("/redirect/:url", (req, res) -> redirect_invalid_url(req, res));
    }
    private static String redirect_invalid_url(Request req, Response res) {
        if(req.params(":url").contains("example.com")){
            return "Invalid URL";
        }
        else {
            return "Valid URL";
        }
    }
}