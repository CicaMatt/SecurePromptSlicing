import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClientRequest(clientSocket);
        }
    }

    private static void handleClientRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.startsWith("GET /")) {
            String[] parts = requestLine.split("\\?");
            if (parts.length > 1) {
                String query = parts[1];
                String[] queryParams = query.split("&");
                for (String param : queryParams) {
                    if (param.startsWith("username=")) {
                        String username = param.substring("username=".length());
                        sendResponse(out, username);
                        break;
                    }
                }
            }
        }

        in.close();
        out.close();
        clientSocket.close();
    }

    private static void sendResponse(OutputStream out, String username) throws IOException {
        PrintWriter writer = new PrintWriter(out, true);

        String response = "HTTP/1.1 200 OK\r\n" +
                          "Content-Type: text/plain\r\n" +
                          "\r\n" +
                          "hello " + username;

        writer.println(response);
    }
}