import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket client = server.accept();
            new Thread(() -> handleRequest(client)).start();
        }
    }

    private static void handleRequest(Socket client) {
        try (
                BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
                PrintWriter out = new PrintWriter(client.getOutputStream(), true)
        ) {
            String requestLine = in.readLine();
            if (requestLine != null && requestLine.startsWith("GET")) {
                String[] parts = requestLine.split("\\?");
                if (parts.length > 1) {
                    String query = parts[1];
                    String[] params = query.split("&");
                    for (String param : params) {
                        if (param.startsWith("username=")) {
                            String username = param.substring("username=".length());
                            http_hello_page(username, out);
                            break;
                        }
                    }
                } else {
                    sendErrorResponse(out);
                }
            } else {
                sendErrorResponse(out);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void http_hello_page(String username, PrintWriter response) {
        String content = "Hello " + username;
        response.println("HTTP/1.1 200 OK");
        response.println("Content-Type: text/html");
        response.println("Content-Length: " + content.length());
        response.println();
        response.println(content);
    }

    private static void sendErrorResponse(PrintWriter response) {
        String errorMessage = "Invalid request";
        response.println("HTTP/1.1 400 Bad Request");
        response.println("Content-Type: text/plain");
        response.println("Content-Length: " + errorMessage.length());
        response.println();
        response.println(errorMessage);
    }
}