import java.util.HashMap;
import java.util.Map;

public class Router {
    private Map<String, Runnable> routes = new HashMap<>();

    public void get(String path, Runnable handler) {
        routes.put(path, handler);
    }

    public String navigate(String path) {
        if (routes.containsKey(path)) {
            return ((Runnable) routes.get(path)).run().toString();
        }
        return "404 Not Found";
    }

    public static class Handler {
        private String username;

        public Handler(String username) {
            this.username = username;
        }

        public String hello() {
            return "Hello " + escape(username);
        }

        private String escape(String input) {
            return input.replace("<", "&lt;").replace(">", "&gt;");
        }
    }

    public static void main(String[] args) {
        Router router = new Router();
        String username = "John Doe";
        Handler handler = new Handler(username);

        router.get("/hello/" + username, () -> handler.hello());

        System.out.println(router.navigate("/hello/" + username));
    }
}