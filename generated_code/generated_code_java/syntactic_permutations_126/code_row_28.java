package helloworld;
import java.io.*;
import java.net.*;
public class Hello {
  public static void main(String[] args) throws Exception {
    ServerSocket listener = new ServerSocket(80);
    try {
      while (true) {
        Socket socket = listener.accept();
        try {
          PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
          BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
          String username = null;
          String line = in.readLine();
          while (!line.isEmpty()) {
            if (line.startsWith("GET /hello")) {
              int startUser = line.indexOf('/', 1) + 1;
              int endUser = line.indexOf(' ', startUser);
              username = line.substring(startUser, endUser);
            }
            line = in.readLine();
          }
          out.println("HTTP/1.1 200 OK");
          out.println("Content-Type: text/html; charset=UTF-8");
          out.println("<html><head></head>");
          out.println("<body>");
          out.println("<h1>" + username + "</h1>");
          out.println("</body></html>");
        } finally {
          socket.close();
        }
      }
    } finally {
      listener.close();
    }
  }
}