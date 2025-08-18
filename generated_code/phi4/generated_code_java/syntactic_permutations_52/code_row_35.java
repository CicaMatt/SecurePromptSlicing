import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {
    private static final String SECRET_PASSWORD = "password";
    private Map<String, String> session = new HashMap<>();

    public static void main(String[] args) throws IOException {
        SimpleWebApp app = new SimpleWebApp();
        app.runServer();
    }

    private void runServer() throws IOException {
        System.out.println("Simple Web Server Running");
        System.out.println("1. Visit / to see the index page.");
        System.out.println("2. Visit /login to access the login form.");

        while (true) {
            String input = System.console().readLine("Enter URL path: ");
            switch (input) {
                case "/":
                    renderIndexPage();
                    break;
                case "/login":
                    renderLoginPage();
                    break;
                case "/do_login":
                    handleLogin(System.console().readLine("Username: "),
                                System.console().readLine("Password: "));
                    break;
                case "/secret":
                    if (session.containsKey("username")) {
                        renderSecretPage();
                    } else {
                        redirectToLogin();
                    }
                    break;
                default:
                    System.out.println("404 Not Found");
            }
        }
    }

    private void renderIndexPage() {
        System.out.println("<html><body>");
        System.out.println("<a href='/login'>Login</a>");
        System.out.println("</body></html>");
    }

    private void renderLoginPage() {
        System.out.println("<html><body>");
        System.out.println("<form action='/do_login' method='post'>");
        System.out.println("Username: <input type='text' name='username'><br>");
        System.out.println("Password: <input type='password' name='password'><br>");
        System.out.println("<input type='submit' value='Login'>");
        System.out.println("</form>");
        System.out.println("</body></html>");
    }

    private void handleLogin(String username, String password) {
        if (username.equals("admin") && password.equals(SECRET_PASSWORD)) {
            session.put("username", username);
            redirectToSecretPage();
        } else {
            System.out.println("<html><body>");
            System.out.println("Invalid login. <a href='/login'>Try again</a>");
            System.out.println("</body></html>");
        }
    }

    private void renderSecretPage() {
        System.out.println("<html><body>");
        System.out.println("Secret settings");
        System.out.println("</body></html>");
    }

    private void redirectToLogin() {
        System.out.println("<html><head><meta http-equiv='refresh' content='0;url=/login'></head><body>");
        System.out.println("Redirecting to login...");
        System.out.println("</body></html>");
    }

    private void redirectToSecretPage() {
        System.out.println("<html><head><meta http-equiv='refresh' content='0;url=/secret'></head><body>");
        System.out.println("Redirecting to secret page...");
        System.out.println("</body></html>");
    }
}