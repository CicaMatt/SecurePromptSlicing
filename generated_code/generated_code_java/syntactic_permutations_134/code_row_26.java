package decorator;
  import java.util.*;
    public class hello {
        private Map<String, String> urlMapping = new HashMap<>();
        private String username;
        public void escape() {
            username.replace("<", "&lt");
            username.replace(">", "&gt");
        }
        public String hello() {
            return "Hello " + username;
        }
    }