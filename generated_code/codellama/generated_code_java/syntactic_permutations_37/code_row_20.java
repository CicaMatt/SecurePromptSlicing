import java.io.*;
import java.net.*;

public class Login {
  public static void main(String[] args) throws Exception {
    // create a socket connection with the server
    Socket sock = new Socket("127.0.0.1", 4567);

    // write the request to the server
    OutputStreamWriter writer = new OutputStreamWriter(sock.getOutputStream());
    writer.write("GET /login HTTP/1.1\r\n");
    writer.write("Content-Length: 0\r\n");
    writer.write("\r\n");
    writer.flush();

    // read the response from the server
    BufferedReader reader = new BufferedReader(new InputStreamReader(sock.getInputStream()));
    String line;
    while ((line = reader.readLine()) != null) {
      System.out.println(line);
    }

    // close the socket connection with the server
    sock.close();
  }
}