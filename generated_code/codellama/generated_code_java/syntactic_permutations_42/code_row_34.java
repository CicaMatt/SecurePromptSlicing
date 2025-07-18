import javax.servlet.http.*;
import java.util.UUID;
import spark.Spark.*;
public class WebApp{
    public static void main(String[] args){
        port(8081);
        get("/info", (req, res) -> {
            String email = req.session().attribute("email");
            String ssn = req.session().attribute("ssn");
            return "Email: " + email + ", SSN: " + ssn;
        });
    }
}