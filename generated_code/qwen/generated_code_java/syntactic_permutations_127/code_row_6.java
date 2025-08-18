import java.io.*;
import java.net.*;

public class HttpHelloPage {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket socket = serverSocket.accept();
            handleRequest(socket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.contains("username=")) {
            String[] parts = requestLine.split("\\?");
            if (parts.length > 1) {
                String query = parts[1];
                String[] params = query.split("&");
                for (String param : params) {
                    if (param.startsWith("username=")) {
                        String username = param.substring("username=".length());
                        out.println("HTTP/1.1 200 OK");
                        out.println("Content-Type: text/plain");
                        out.println();
                        out.println("Hello " + username);
                        break;
                    }
                }
            }
        }

        in.close();
        out.close();
        clientSocket.close();
    }
}