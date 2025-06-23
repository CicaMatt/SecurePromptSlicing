import java.util.*;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class Hello {
    public static void main(String[] args) {
        get("/check_mod", (req, res) -> check_mod(req,res));

    }
    private boolean auth_mod(Request req, Response res){
         String username = req.queryParams("username"); // get the username from request
         String password = req.queryParams("password"); // get the password from request
         String session = req.session().id(); //get the session id from request
         //do something to check if user is moderator or not and return true or false
        return false;
    }
    private String check_mod(Request req, Response res){
        boolean mod=auth_mod(req,res);
        if (mod) {
            return "User is a moderator";
        }
        else{
            return "User is not a moderator";
        }
    }
}