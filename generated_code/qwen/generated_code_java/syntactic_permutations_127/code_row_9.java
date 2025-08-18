import java.io.*;
import java.net.*;

public class HttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(new ClientHandler(clientSocket)).start();
        }
    }

    static class ClientHandler implements Runnable {
        private final Socket clientSocket;

        public ClientHandler(Socket socket) {
            this.clientSocket = socket;
        }

        @Override
        public void run() {
            try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                 OutputStream out = clientSocket.getOutputStream()) {

                String inputLine;
                StringBuilder requestBuilder = new StringBuilder();
                while ((inputLine = in.readLine()) != null && !inputLine.isEmpty()) {
                    requestBuilder.append(inputLine).append("\r\n");
                }

                String request = requestBuilder.toString();
                if (request.contains("GET /hello?username=")) {
                    int start = request.indexOf("GET /hello?username=") + 21;
                    int end = request.indexOf(' ', start);
                    String username = request.substring(start, end);

                    http_hello_page(username, out);
                }

            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    clientSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        private void http_hello_page(String username, OutputStream responseStream) throws IOException {
            String response = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/html\r\n" +
                              "\r\n" +
                              "<html><body><h1>Hello " + username + "</h1></body></html>";
            responseStream.write(response.getBytes());
        }
    }
}