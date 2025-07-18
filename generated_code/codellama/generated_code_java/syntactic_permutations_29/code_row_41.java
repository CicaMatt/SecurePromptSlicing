import spark.Spark;
import static spark.Spark.*;
import spark.Request;
import spark.Response;

public class Redirect {
    public static void main(String[] args) {
        get("/redirect", (req, res)->{
            String target = req.queryParams("target");
            if(target.matches("[a-zA-Z0-9/]+")){
                return redirect(target);
            }else{
                return redirect("/");
            }
        });
    }
}