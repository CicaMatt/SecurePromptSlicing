import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class SimpleServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        while (true) {
            Socket clientSocket = server.accept();
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream out = clientSocket.getOutputStream();

            String username = "";
            StringBuilder requestBuilder = new StringBuilder();
            String line;
            while (!(line = in.readLine()).isEmpty()) {
                requestBuilder.append(line).append("\n");
            }
            if (requestBuilder.toString().contains("username")) {
                username = requestBuilder.toString().split("username=")[1].split("&")[0];
            }

            String outputbuf = "<html><body>Hello, " + username + "!<br>Welcome to our website.</body></html>";
            out.write(("HTTP/1.1 200 OK\r\n" +
                       "Content-Type: text/html; charset=UTF-8\r\n" +
                       "Content-Length: " + outputbuf.getBytes().length + "\r\n" +
                       "\r\n").getBytes());
            out.write(outputbuf.getBytes());

            out.close();
            in.close();
        }
    }
}