import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Scanner;

public class WebApp {

    public static void main(String[] args) {
        try {
            login();
            doLogin("username", "password");
            index();
            userPage();
            adminPage();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void login() throws IOException {
        URL url = new URL("http://example.com/login");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET");

        int responseCode = connection.getResponseCode();
        System.out.println("Response Code for login: " + responseCode);

        try (BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
            String inputLine;
            StringBuilder content = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            System.out.println("Login Page Content:\n" + content.toString());
        }
    }

    public static void doLogin(String username, String password) throws IOException {
        URL url = new URL("http://example.com/do_login");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("POST");
        connection.setDoOutput(true);
        
        String postData = "username=" + java.net.URLEncoder.encode(username, "UTF-8") +
                          "&password=" + java.net.URLEncoder.encode(password, "UTF-8");

        try (DataOutputStream out = new DataOutputStream(connection.getOutputStream())) {
            out.writeBytes(postData);
            out.flush();
        }

        int responseCode = connection.getResponseCode();
        System.out.println("Response Code for doLogin: " + responseCode);

        try (BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
            String inputLine;
            StringBuilder content = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            System.out.println("Do Login Response Content:\n" + content.toString());
        }
    }

    public static void index() throws IOException {
        URL url = new URL("http://example.com/index");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET");

        int responseCode = connection.getResponseCode();
        System.out.println("Response Code for index: " + responseCode);

        try (BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
            String inputLine;
            StringBuilder content = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            System.out.println("Index Page Content:\n" + content.toString());
        }
    }

    public static void userPage() throws IOException {
        URL url = new URL("http://example.com/user_page");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET");

        int responseCode = connection.getResponseCode();
        System.out.println("Response Code for userPage: " + responseCode);

        try (BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
            String inputLine;
            StringBuilder content = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            System.out.println("User Page Content:\n" + content.toString());
        }
    }

    public static void adminPage() throws IOException {
        URL url = new URL("http://example.com/admin_page");
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET");

        int responseCode = connection.getResponseCode();
        System.out.println("Response Code for adminPage: " + responseCode);

        try (BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
            String inputLine;
            StringBuilder content = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            System.out.println("Admin Page Content:\n" + content.toString());
        }
    }
}