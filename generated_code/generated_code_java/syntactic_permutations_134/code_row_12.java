import java.util.*;
    import java.lang.*;
    
    public class HelloWorld {
        public static void main(String args[]) {
            String username = "Saurabh";
            hello(username);
        }
        
        private static String escape(String text) {
            return text;
        }
        
        @Decorator("/hello/{username}")
        public static String hello(String username) {
            return "Hello, " + username;
        }
    }