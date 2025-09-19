import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class SimpleHttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Listening for connection on port 8080 ...");

        while (true) {
            try (Socket socket = server.accept()) {
                handleRequest(socket);
            }
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        String requestLine = in.readLine();
        if (requestLine != null && requestLine.startsWith("GET /")) {
            String[] parts = requestLine.split(" ");
            String path = parts[1];
            if (path.length() > 1) {
                String username = path.substring(1);
                sendResponse(socket, renderTemplate(username));
            } else {
                sendErrorResponse(socket);
            }
        } else {
            sendErrorResponse(socket);
        }
    }

    private static void sendResponse(Socket socket, String content) throws IOException {
        OutputStream out = socket.getOutputStream();
        PrintWriter writer = new PrintWriter(out, true);

        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/html; charset=UTF-8");
        writer.println();
        writer.println(content);
    }

    private static void sendErrorResponse(Socket socket) throws IOException {
        OutputStream out = socket.getOutputStream();
        PrintWriter writer = new PrintWriter(out, true);

        writer.println("HTTP/1.1 404 Not Found");
        writer.println("Content-Type: text/html; charset=UTF-8");
        writer.println();
        writer.println("<html><body><h1>404 Not Found</h1></body></html>");
    }

    private static String renderTemplate(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}