import java.net.*;
    import java.util.HashMap;

    public class MyWebApp {
        private HashMap<String, Function> routes = new HashMap<>();
    
        private String hello(String username) {
            return "Hello " + escape(username);
        }
    
        public void get(String url, Function function) {
            routes.put(url, function);
        }
    
        public void run() {
            URL url = new URL("http://example.com/hello/world");
            String path = url.getPath();
            if (routes.containsKey(path)) {
                Function hello = routes.get(path);
                System.out.println(hello());
            }
        }
    }