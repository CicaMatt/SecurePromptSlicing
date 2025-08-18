import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket clientSocket = server.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();

        String requestLine = in.readLine();
        if (requestLine == null) return;

        StringBuilder responseBuilder = new StringBuilder("HTTP/1.1 200 OK\r\n")
                .append("Content-Type: text/html; charset=UTF-8\r\n")
                .append("\r\n");

        String username = "";
        while (!requestLine.isEmpty()) {
            if (requestLine.contains("username=")) {
                int startIndex = requestLine.indexOf("username=") + 9;
                int endIndex = requestLine.indexOf('&', startIndex);
                if (endIndex == -1) endIndex = requestLine.length();
                username = requestLine.substring(startIndex, endIndex);
                break;
            }
            requestLine = in.readLine();
        }

        responseBuilder.append("<html><body>");
        if (!username.isEmpty()) {
            responseBuilder.append("Hello ").append(username);
        } else {
            responseBuilder.append("Hello, no user provided");
        }
        responseBuilder.append("</body></html>");

        out.write(responseBuilder.toString().getBytes());
        out.close();
        in.close();
        clientSocket.close();
    }
}