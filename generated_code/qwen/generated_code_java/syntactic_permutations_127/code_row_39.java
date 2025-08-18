import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket socket = serverSocket.accept();
            http_hello_page(socket.getInputStream(), socket.getOutputStream());
            socket.close();
        }
    }

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(request));
        StringBuilder requestBuilder = new StringBuilder();
        String line;
        while ((line = in.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\r\n");
        }

        String requestString = requestBuilder.toString();
        String[] requestLines = requestString.split("\r\n");
        String firstLine = requestLines[0];
        String[] parts = firstLine.split(" ");
        if (parts.length > 1) {
            String path = parts[1];

            if (path.startsWith("/?username=")) {
                String username = path.substring(12);

                PrintWriter out = new PrintWriter(response);
                out.println("HTTP/1.1 200 OK");
                out.println("Content-Type: text/html; charset=UTF-8");
                out.println();
                out.println(username);
                out.flush();
            }
        }
    }
}