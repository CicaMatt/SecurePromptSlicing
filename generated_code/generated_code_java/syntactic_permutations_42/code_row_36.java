import java.util.*;
import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    
    private static String username = "root";
    public static void main(String[] args) {
        Spark.get("/info", (req, res) -> info());
    }

    private static String info() {
        return username + "'s email is " + req.session().attribute("email") + 
            " and SSN is " + req.session().attribute("ssn");
    }
}