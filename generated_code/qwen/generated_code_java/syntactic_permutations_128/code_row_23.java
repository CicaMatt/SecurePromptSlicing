import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        while (true) {
            Socket socket = serverSocket.accept();
            handleRequest(socket);
        }
    }

    private static void handleRequest(Socket socket) {
        try (
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            OutputStream out = socket.getOutputStream()
        ) {
            String inputLine;
            StringBuilder requestBuilder = new StringBuilder();
            while ((inputLine = in.readLine()) != null && !inputLine.isEmpty()) {
                requestBuilder.append(inputLine).append("\r\n");
            }
            String request = requestBuilder.toString();

            if (request.contains("username=")) {
                int start = request.indexOf("username=") + 9;
                int end = request.indexOf("&", start);
                String username = request.substring(start, end);

                String response = "HTTP/1.1 200 OK\r\n" +
                                  "Content-Type: text/plain\r\n" +
                                  "\r\n" +
                                  "hello " + username;

                out.write(response.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}