import java.io.*;

class http_hello_page {
  public static void main(String[] args) throws IOException {
      BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
      String username = reader.readLine();
      System.out.println("hello " + username);
  }
}