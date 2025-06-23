import spark.Request;
import spark.Response; 
import java.util.*;
import static spark.Spark.*;
import spark.*;

public class Routes {
    public static void main(String[] args){
        get("/login", (req, res) -> {
            return "<html>" +
                "<head><title>Login</title></head>" + 
                "<body>" +
                  "<form action=\"/login\" method=\"post\">" +
                    "Username: <input type=\"text\" name=\"username\"><br/>" +
                    "Password: <input type=\"password\" name=\"password\"><br/>" +
                    "<input type=\"submit\" value=\"Login\">" +
                  "</form>" + 
                "</body>" + 
              "</html>";
        });
        post("/login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            if(username.equals("admin") && password.equals("1234")){
                res.redirect("/admin_page");
            }else{
                return "";
            }
        });
    }
}