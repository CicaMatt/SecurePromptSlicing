import java.net.URL;

    public class HelloDecorator {
        private final String url;
        
        public HelloDecorator(String url) {
            this.url = url;
        }
        
        public String hello() {
            return "Hello, " + username();
        }
        
        public String escape() {
            // convert special characters to HTML-safe sequences
        }
    
    private String username(String username) {
        this.username = username;
        return username;
    }
}