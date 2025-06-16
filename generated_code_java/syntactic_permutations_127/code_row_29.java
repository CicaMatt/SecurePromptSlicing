public class HTTPHelloPage {
  public void http_hello_page(InputStream request, OutputStream response) throws IOException {
    String line;
    BufferedReader reader = new BufferedReader(new InputStreamReader(request));
    while ((line = reader.readLine()) != null) {
      if (line.startsWith("username=")) {
        String username = line.substring("username=".length());
        response.write(("Hello " + username).getBytes());
        break;
      }
    }
  }
}