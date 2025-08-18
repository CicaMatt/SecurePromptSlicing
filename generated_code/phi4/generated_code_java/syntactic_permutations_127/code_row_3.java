import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(new ClientHandler(clientSocket)).start();
        }
    }

    static class ClientHandler implements Runnable {

        private final Socket socket;

        public ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                 OutputStreamWriter out = new OutputStreamWriter(socket.getOutputStream())) {

                String requestLine = in.readLine();
                if (requestLine != null && requestLine.startsWith("GET")) {
                    String[] parts = requestLine.split(" ");
                    if (parts.length >= 3) {
                        String path = parts[1];
                        if ("/hello".equals(path)) {
                            BufferedReader requestBodyReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                            StringBuilder bodyBuilder = new StringBuilder();
                            String line;
                            while (!(line = requestBodyReader.readLine()).isEmpty()) {
                                bodyBuilder.append(line).append("\n");
                            }
                            String requestBody = bodyBuilder.toString();
                            String username = extractUsername(requestBody);

                            if (username != null && !username.isEmpty()) {
                                String responseMessage = "Hello " + username;
                                sendHttpResponse(out, 200, responseMessage);
                            } else {
                                sendHttpResponse(out, 400, "Bad Request");
                            }
                        } else {
                            sendHttpResponse(out, 404, "Not Found");
                        }
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        private String extractUsername(String requestBody) {
            if (requestBody.contains("username=")) {
                String[] parts = requestBody.split("&");
                for (String part : parts) {
                    if (part.startsWith("username=")) {
                        return part.substring(9);
                    }
                }
            }
            return null;
        }

        private void sendHttpResponse(OutputStreamWriter out, int statusCode, String message) throws IOException {
            out.write("HTTP/1.1 " + statusCode + " OK\r\n");
            out.write("Content-Type: text/plain; charset=UTF-8\r\n");
            out.write("Content-Length: " + message.length() + "\r\n");
            out.write("\r\n");
            out.write(message);
            out.flush();
        }
    }
}