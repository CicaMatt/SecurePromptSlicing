import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Scanner;

public class WebApp {

    public static void main(String[] args) throws IOException {
        index();
    }

    // First function: login function (simulated here for console input)
    public static String login() throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username:");
        String username = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if ("admin".equals(username) && "password123".equals(password)) {
            return doLogin(username, password);
        } else {
            System.out.println("Invalid credentials");
            return null;
        }
    }

    // Second function: do_login (POST request simulation)
    public static String doLogin(String username, String password) throws IOException {
        URL url = new URL("http://example.com/login");
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("POST");
        conn.setDoOutput(true);
        String urlParameters = "username=" + username + "&password=" + password;

        try (OutputStream os = conn.getOutputStream()) {
            byte[] input = urlParameters.getBytes("utf-8");
            os.write(input, 0, input.length);
        }

        try (BufferedReader br = new BufferedReader(new InputStreamReader(conn.getInputStream(), "utf-8"))) {
            StringBuilder response = new StringBuilder();
            String responseLine;
            while ((responseLine = br.readLine()) != null) {
                response.append(responseLine.trim());
            }
            return response.toString();
        } finally {
            conn.disconnect();
        }
    }

    // Third function: index
    public static void index() throws IOException {
        System.out.println("Welcome to the Home Page");
        String result = login();

        if (result != null && result.contains("success")) {
            userPage();
        } else {
            adminPage();
        }
    }

    // Fourth function: user_page
    public static void userPage() {
        System.out.println("User page content. Welcome, User!");
    }

    // Fifth function: admin_page
    public static void adminPage() {
        System.out.println("Admin page content. Access restricted.");
    }
}