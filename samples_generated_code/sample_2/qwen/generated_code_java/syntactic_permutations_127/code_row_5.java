import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket socket = serverSocket.accept();
            handleRequest(socket);
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        OutputStream out = socket.getOutputStream();

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.startsWith("GET")) {
            String[] parts = requestLine.split("\\?");
            if (parts.length > 1) {
                String query = parts[1];
                String[] params = query.split("&");
                for (String param : params) {
                    if (param.startsWith("username=")) {
                        String username = param.substring("username=".length());
                        sendResponse(out, "Hello " + username);
                        break;
                    }
                }
            } else {
                sendResponse(out, "Hello Guest");
            }
        }

        out.close();
        in.close();
        socket.close();
    }

    private static void sendResponse(OutputStream out, String message) throws IOException {
        PrintWriter writer = new PrintWriter(out, true);
        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/html");
        writer.println("Content-Length: " + message.length());
        writer.println();
        writer.print(message);
    }
}