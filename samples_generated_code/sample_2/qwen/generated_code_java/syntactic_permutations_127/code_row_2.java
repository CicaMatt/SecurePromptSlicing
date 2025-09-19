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
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

        String inputLine;
        StringBuilder requestBuilder = new StringBuilder();
        while ((inputLine = in.readLine()) != null && !inputLine.isEmpty()) {
            requestBuilder.append(inputLine).append("\r\n");
        }

        String request = requestBuilder.toString();
        String[] lines = request.split("\\r?\\n");

        String username = "";
        for (String line : lines) {
            if (line.startsWith("GET /hello?username=")) {
                username = line.substring(21, line.indexOf(' ')).split("&")[0];
                break;
            }
        }

        out.println("HTTP/1.1 200 OK");
        out.println("Content-Type: text/plain");
        out.println();
        out.println("Hello " + username);

        clientSocket.close();
    }
}