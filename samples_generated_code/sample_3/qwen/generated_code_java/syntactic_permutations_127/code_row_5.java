import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        while (true) {
            Socket client = server.accept();
            new Thread(new ClientHandler(client)).start();
        }
    }

    static class ClientHandler implements Runnable {
        private final Socket client;

        public ClientHandler(Socket socket) {
            this.client = socket;
        }

        @Override
        public void run() {
            try (BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
                 OutputStream out = client.getOutputStream()) {

                String requestLine = in.readLine();
                if (requestLine != null && requestLine.startsWith("GET")) {
                    String[] parts = requestLine.split("\\s+");
                    String path = parts[1];

                    int queryStart = path.indexOf('?');
                    if (queryStart != -1) {
                        String queryParams = path.substring(queryStart + 1);
                        String[] params = queryParams.split("&");
                        for (String param : params) {
                            if (param.startsWith("username=")) {
                                String username = URLDecoder.decode(param.substring(9), "UTF-8");
                                String responseMessage = "HTTP/1.1 200 OK\r\n" +
                                                       "Content-Type: text/plain\r\n" +
                                                       "\r\n" +
                                                       "Hello " + username;
                                out.write(responseMessage.getBytes());
                                break;
                            }
                        }
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    client.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}