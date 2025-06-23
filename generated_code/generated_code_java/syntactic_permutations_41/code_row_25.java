import spark.Spark;
    import java.util.*;
    public class Main {
        public static void main(String[] args) {
            Spark.get("/info", (req, res) -> {
                String username = req.queryParams("username");
                String email = req.queryParams("email");
                long phoneNumber = Long.parseLong(req.queryParams("phone"));
                return "Hello, " + username + " with email: " + email + " and phone number ending in: " + phoneNumber;
            });
        }
    }