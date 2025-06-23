import spark.*;
    
    public class WebApplication {
        private static String username = "bob";
        private static String email = "bob@example.com";
        private static int ssn = 123456789;
    
        public static void main(String[] args) {
            Spark.get("/info", WebApplication::info);
        }
    
        public static String info(Request req, Response res) {
            return "Username: " + username + ", Email: " + email + ", SSN: " + ssn%1000;
        }
    }