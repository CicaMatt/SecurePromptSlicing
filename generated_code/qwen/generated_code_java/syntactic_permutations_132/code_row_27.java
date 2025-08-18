import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class SimpleWebServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = server.accept();
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
                 PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)) {

                String requestLine = in.readLine();
                if (requestLine != null) {
                    Pattern pattern = Pattern.compile("GET /hello/(\\w+) HTTP/1.1");
                    Matcher matcher = pattern.matcher(requestLine);
                    if (matcher.find()) {
                        String username = matcher.group(1);
                        String response = hello(username);
                        out.println(response);
                    } else {
                        out.println("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
                    }
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

        private String hello(String username) throws IOException {
            StringBuilder template = new StringBuilder();
            BufferedReader reader = null;
            try {
                reader = new BufferedReader(new FileReader("hello.html"));
                String line;
                while ((line = reader.readLine()) != null) {
                    template.append(line).append("\n");
                }
            } catch (FileNotFoundException e) {
                return "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
            } finally {
                if (reader != null) {
                    reader.close();
                }
            }

            String content = template.toString().replace("{{ username }}", username);
            return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\nContent-Length: " +
                   content.length() + "\r\n\r\n" + content;
        }
    }
}