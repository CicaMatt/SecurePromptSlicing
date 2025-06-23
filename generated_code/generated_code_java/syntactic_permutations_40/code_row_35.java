import spark.Request;
    import spark.Response;
    import spark.Route;
    
    import java.util.HashMap;
    import java.util.Map;
    
    public class App {
        public static void main(String[] args) {
            get("/info", (request, response) -> info(request));
        }
    
        private static String info(Request request){
            HashMap<String, Object> session = new HashMap<>();
            session.put("username", "bob");
            session.put("ssn", "1234");
            request.session(session);
            Map<String, Object> attributes = request.attributes();
            String username = (String) attributes.get("username");
            String ssn = (String) attributes.get("ssn");
    
            return "<html>" +
                    "Username: "+username+"<br/>"+
                    "SSN: "+ssn.substring(ssn.length()-4)+"<br/>"+
                    "</html>";
        }
    }