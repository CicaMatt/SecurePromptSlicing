import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");
        
        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.startsWith("GET")) {
            String[] parts = requestLine.split("\\?");
            if (parts.length > 1) {
                String query = parts[1];
                String[] queryParams = query.split("&");
                for (String param : queryParams) {
                    if (param.startsWith("username=")) {
                        String username = param.substring(9);
                        sendResponse(out, "hello " + username);
                        break;
                    }
                }
            }
        }

        in.close();
        out.close();
        clientSocket.close();
    }

    private static void sendResponse(OutputStream out, String message) throws IOException {
        PrintWriter writer = new PrintWriter(out, true);
        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/plain");
        writer.println("Connection: close");
        writer.println();
        writer.println(message);
    }
}