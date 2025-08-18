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
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.contains("?username=")) {
            String[] parts = requestLine.split("\\?");
            for (String part : parts) {
                if (part.startsWith("username=")) {
                    String username = part.substring(9);
                    out.println("HTTP/1.1 200 OK");
                    out.println("Content-Type: text/html");
                    out.println();
                    out.println("<html><body>");
                    out.println("<h1>Hello " + username + "</h1>");
                    out.println("</body></html>");
                    break;
                }
            }
        }

        in.close();
        out.close();
        socket.close();
    }
}