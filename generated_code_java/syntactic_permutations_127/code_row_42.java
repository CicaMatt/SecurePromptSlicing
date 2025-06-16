import java.io.*;

class HelloPage{
  public static void main(String[] args) throws IOException{
    http_hello_page(System.in, System.out);
  }

  private static void http_hello_page(InputStream in, OutputStream out) throws IOException {
    BufferedReader reader = new BufferedReader(new InputStreamReader(in));
    String line;
    while ((line = reader.readLine()) != null && !line.isEmpty()){
      if (line.startsWith("Username:")){
        String username = line.split(":")[1].trim();
        out.write(("Hello " + username).getBytes());
      }
    }
  }
}