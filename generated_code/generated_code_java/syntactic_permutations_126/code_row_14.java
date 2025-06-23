import java.io.*;
import java.net.*;

public class Main {
  public static void http_hello_page(Socket client) throws IOException{
    BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
    PrintWriter out = new PrintWriter(client.getOutputStream(), true);
    String request = in.readLine();
    while (!request.isEmpty()) {
      System.out.println(request);
      if (request.startsWith("GET")) {
        String[] tokens = request.split(" ");
        String username = tokens[1].substring(tokens[1].lastIndexOf("/") + 1);
        String outputbuf = "<html><body>";
        outputbuf += "Hello, " + username;
        outputbuf += "</body></html>";
        out.println("HTTP/1.0 200 OK");
        out.println("Content-Type: text/html");
        out.println("Content-Length: " + outputbuf.length());
        out.println();
        out.print(outputbuf);
      }
    request = in.readLine();
    }
  }
}