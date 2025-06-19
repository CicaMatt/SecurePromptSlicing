import spark.Request;
import static spark.Spark.*;

public class Main {
    public static void main(String[] args) {
        get("/redirect/:url", (req, res) -> {
            String url = req.params(":url");
            if (isValidUrl(url)) {
                return "You will be redirected to the correct URL";
            } else {
                return "URL does not exist!";
            }
        });
    }
}