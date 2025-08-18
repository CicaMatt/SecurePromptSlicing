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

        String inputLine;
        StringBuilder requestBody = new StringBuilder();
        boolean readingBody = false;

        while ((inputLine = in.readLine()) != null) {
            if (inputLine.startsWith("POST /hello")) {
                readingBody = true;
            } else if (readingBody && inputLine.isEmpty()) {
                continue; // Skip the blank line between headers and body
            } else if (readingBody) {
                requestBody.append(inputLine);
                break; // Assuming single line request body for simplicity
            }
        }

        String username = requestBody.toString().trim();
        String response =
                "HTTP/1.1 200 OK\r\n" +
                "Content-Type: text/html\r\n" +
                "\r\n" +
                "<html><body>Hello, " + htmlEscape(username) + "!</body></html>";

        out.write(response.getBytes());
        out.flush();
        clientSocket.close();
    }

    private static String htmlEscape(String input) {
        if (input == null) return "";
        StringBuilder sb = new StringBuilder(input.length() * 2);
        for (char c : input.toCharArray()) {
            switch(c) {
                case '<': sb.append("&lt;"); break;
                case '>': sb.append("&gt;"); break;
                case '&': sb.append("&amp;"); break;
                case '"': sb.append("&quot;"); break;
                default: sb.append(c); break;
            }
        }
        return sb.toString();
    }
}