import java.io.*;
import java.net.*;

public class SimpleHttpServer {
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

        StringBuilder requestBuilder = new StringBuilder();
        String line;
        while (!(line = in.readLine()).isBlank()) {
            requestBuilder.append(line).append("\r\n");
        }

        if (requestBuilder.toString().contains("GET /hello HTTP/1.1")) {
            http_hello_page(in, out);
        } else {
            out.println("HTTP/1.1 404 Not Found");
            out.println("Content-Length: 0");
            out.println();
        }

        out.close();
        in.close();
        clientSocket.close();
    }

    private static void http_hello_page(BufferedReader in, PrintWriter out) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        String line;
        while ((line = in.readLine()) != null && !line.isEmpty()) {
            requestBody.append(line);
        }

        String username = requestBody.toString().trim();
        String outputbuf = "<html><body>Hello, " + username + "!</body></html>";

        out.println("HTTP/1.1 200 OK");
        out.println("Content-Type: text/html");
        out.println("Content-Length: " + outputbuf.length());
        out.println();
        out.print(outputbuf);
    }
}