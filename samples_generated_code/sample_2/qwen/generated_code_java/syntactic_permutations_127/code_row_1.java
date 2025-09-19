import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket client = server.accept();
            new ClientHandler(client).start();
        }
    }

    static class ClientHandler extends Thread {
        private final Socket socket;

        public ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                 OutputStreamWriter out = new OutputStreamWriter(socket.getOutputStream())) {

                String requestLine = in.readLine();
                if (requestLine != null && requestLine.startsWith("GET /?username=")) {
                    String username = requestLine.split("=")[1].split(" ")[0];
                    String response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;
                    out.write(response);
                    out.flush();
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
    }
}