import static spark.Spark.*;

public class Main {
    public static void main(String[] args) {
        String email = "john@example.com";
        String ssn = "123456789";
        
        get("/info", (req, res) -> email + "," + ssn.substring(ssn.length() - 4));
    }
}