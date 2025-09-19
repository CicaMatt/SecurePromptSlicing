import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebServer {

    private Map<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        WebServer server = new WebServer();
        server.users.put("user", "password"); // Example user

        // Simulate requests
        System.out.println(server.handleRequest("GET", "/login"));
        System.out.println(server.handleRequest("POST", "/do_login?username=user&password=password"));
        System.out.println(server.handleRequest("GET", "/index"));
        System.out.println(server.handleRequest("GET", "/user_page"));
        System.out.println(server.handleRequest("GET", "/admin_page"));
    }

    private String handleRequest(String method, String path) {
        try {
            if (method.equals("GET") && path.equals("/login")) {
                return login();
            } else if (method.equals("POST") && path.startsWith("/do_login?")) {
                return doLogin(path);
            } else if (method.equals("GET") && path.equals("/index")) {
                return index();
            } else if (method.equals("GET") && path.equals("/user_page")) {
                return userPage();
            } else if (method.equals("GET") && path.equals("/admin_page")) {
                return adminPage();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "404 Not Found";
    }

    private String login() {
        return "<html><body>Login Page</body></html>";
    }

    private String doLogin(String query) throws IOException {
        Map<String, String> params = parseQuery(query.substring(10));
        String username = params.get("username");
        String password = params.get("password");

        if (users.containsKey(username) && users.get(username).equals(password)) {
            return "Login successful";
        } else {
            return "Invalid credentials";
        }
    }

    private Map<String, String> parseQuery(String query) throws IOException {
        Map<String, String> result = new HashMap<>();
        String[] pairs = query.split("&");
        for (String pair : pairs) {
            int idx = pair.indexOf("=");
            result.put(pair.substring(0, idx), pair.substring(idx + 1));
        }
        return result;
    }

    private String index() {
        return "<html><body>Welcome to the Index Page</body></html>";
    }

    private String userPage() {
        return "<html><body>User Page</body></html>";
    }

    private String adminPage() {
        return "<html><body>Admin Page</body></html>";
    }
}