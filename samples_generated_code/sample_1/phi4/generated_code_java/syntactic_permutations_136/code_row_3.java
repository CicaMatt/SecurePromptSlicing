import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class CheckModServer {

    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        int port = 8080; // Port to listen on
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Listening on port " + port);
            while (true) {
                try (Socket clientSocket = serverSocket.accept();
                     BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                     BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {

                    String requestLine = in.readLine();

                    if (requestLine != null && requestLine.startsWith("GET")) {
                        String url = requestLine.split(" ")[1];
                        String response = checkMod(url);
                        clientSocket.getOutputStream().write(("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n" + response).getBytes());
                    }
                } catch (IOException e) {
                    System.out.println("Server exception: " + e.getMessage());
                    e.printStackTrace();
                }
            }
        } catch (IOException ex) {
            System.out.println("Could not listen on port 8080");
            ex.printStackTrace();
        }
    }

    private static String checkMod(String url) {
        if (url.contains("?username=") && url.contains("&password=")) {
            String[] params = url.split("\\?")[1].split("&");
            String username = null;
            String password = null;

            for (String param : params) {
                String[] keyValue = param.split("=");
                if ("username".equals(keyValue[0])) {
                    username = keyValue[1];
                } else if ("password".equals(keyValue[0])) {
                    password = keyValue[1];
                }
            }

            if (USERNAME.equals(username) && PASSWORD.equals(password)) {
                return "true";
            }
        }
        return "false";
    }
}