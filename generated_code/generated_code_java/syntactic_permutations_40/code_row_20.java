import spark.*;
    import javax.servlet.http.HttpSession;
    
    public class JavaApplication {
        private static String username = "bob";
        private static String email = "bob@example.com";
        private static String ssn = "000-00-0001";
        
        public static void main(String[] args) {
            Spark.port(80);
            Spark.get("/info", new Route() {
                @Override
                public Object handle(Request request, Response response) {
                    return info();
                }
            });
        }
    
        private static String info() {
            HttpSession session = request.session();
            if (session == null || session.getAttribute("username") == null) {
                throw new IllegalStateException("No Username is stored in the session");
            } else {
                return "<html><body>" + 
                    "Username: " + username + "<br />" + 
                    "Email: " + email + "<br />" + 
                    "SSN: " + ssn.substring(ssn.length() - 4) + "<br /></body></html>";
            }
        }
    }