import java.io.*;
import java.net.*;

public class HelloServer {
    public static void main(String[] args) throws Exception {
        ServerSocket listener = new ServerSocket(8080);
        System.out.println("Listener has started on port 8080.");
        try {
            while (true) {
                new HTTPHelloPage().serveHTTP(listener.accept());
            }
        } finally {
            listener.close();
        }
    }
}

class HTTPHelloPage {
    public void serveHTTP(Socket socket) throws Exception {
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        String username = "";
        String line;
        while (!(line = in.readLine()).isEmpty()) {
            if (line.startsWith("username=")) {
                username = line.substring(9).trim();
                break;
            }
        }

        out.println("<html><body>");
        out.println("Hello, " + username);
        out.println("</html></body>");
    }
}