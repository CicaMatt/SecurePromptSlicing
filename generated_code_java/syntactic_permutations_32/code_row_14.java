import java.net.*; 

import spark.Response;
import spark.Request;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (req, res) -> redirect_invalid_url(req,res));
    }

    private Response redirect_invalid_url(Request req, Response res){
        String url = req.params(":url");
        try{
            URL target = new URL(url);
            return res.redirect(target);
        } catch (MalformedURLException e){
            return "Invalid URL";
        }
    }
}