import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

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
        OutputStream out = clientSocket.getOutputStream();

        String line;
        StringBuilder requestBody = new StringBuilder();
        boolean readingBody = false;

        while ((line = in.readLine()) != null) {
            if (line.isEmpty()) {
                readingBody = true;
                continue;
            }
            if (readingBody) {
                requestBody.append(line);
            }
            if (line.startsWith("GET /hello")) {
                String username = requestBody.toString().trim();
                String outputbuf = "<html><body>Hello, " + username + "!</body></html>";
                out.write(("HTTP/1.1 200 OK\r\nContent-Length: " + outputbuf.length() + "\r\nContent-Type: text/html\r\n\r\n").getBytes());
                out.write(outputbuf.getBytes());
                break;
            }
        }

        in.close();
        out.close();
        clientSocket.close();
    }
}