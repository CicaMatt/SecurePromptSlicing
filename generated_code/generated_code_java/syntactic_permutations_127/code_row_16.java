import java.io.*;
public class http_hello_page {
  public static void main(String[] args) throws IOException {
    // request is a file stream that we can write to in order to send a response to the client
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String username = br.readLine();
    PrintWriter pw = new PrintWriter(System.out);
    pw.println("Hello " + username);
    pw.flush();
  }
}