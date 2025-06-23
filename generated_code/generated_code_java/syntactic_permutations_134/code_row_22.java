import java.util.HashMap;
    import java.util.Map;

    public class Decorator {
        private Map<String, String> urlMap = new HashMap<>();
    
        public void map(String url, String funcName) {
            urlMap.put(url, funcName);
        }
    
        public String getFunction(String url) {
            return urlMap.get(url);
        }
    }

    public class Hello {
        private String username;
    
        public Hello(String username) {
            this.username = username;
        }
    
        @Override
        public String toString() {
            return "Hello " + escape(username);
        }
    
        public static String escape(String s) {
            // TODO: implement escaping
            return s;
        }
    }