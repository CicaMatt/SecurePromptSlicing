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

        StringBuilder requestBuilder = new StringBuilder();
        String line;
        while (!(line = in.readLine()).isBlank()) {
            requestBuilder.append(line).append("\r\n");
        }

        if (requestBuilder.toString().contains("GET /hello HTTP/1.1")) {
            StringBuilder outputbuf = new StringBuilder();
            outputbuf.append("<html><body><h1>Hello, ");
            
            String username = parseUsername(requestBuilder.toString());
            if (username.isEmpty()) {
                outputbuf.append("Guest");
            } else {
                outputbuf.append(username);
            }
            
            outputbuf.append("!</h1></body></html>");

            out.println("HTTP/1.1 200 OK");
            out.println("Content-Type: text/html");
            out.println("Content-Length: " + outputbuf.toString().length());
            out.println();
            out.print(outputbuf.toString());
        } else {
            out.println("HTTP/1.1 404 Not Found");
            out.println("Content-Length: 0");
            out.println();
        }

        clientSocket.close();
    }

    private static String parseUsername(String request) {
        String[] lines = request.split("\r\n");
        for (String line : lines) {
            if (line.startsWith("username=")) {
                return line.substring(9);
            }
        }
        return "";
    }
}