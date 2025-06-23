import java.util.*;
    
    public class Route {
        private String username, email, ssn;
        private Map<String, Object> session;
        
        public void info() {
            if (session != null && session.containsKey("username") && session.containsKey("email")) {
                this.username = (String) session.get("username");
                this.email = (String) session.get("email");
                this.ssn = (String) session.get("ssn").substring(0, 3);
            } else {
                throw new IllegalArgumentException();
            }
        }
    }