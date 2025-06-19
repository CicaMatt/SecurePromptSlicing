import java.io.*;

class Hello {
  public static void main(String[] args) throws Exception {
    http_hello_page(System.in, System.out);
  }

  static void http_hello_page(InputStream request, OutputStream response) throws IOException {
    String username = getUsernameFromRequest(request);
    sendResponse(response, "Hello " + username);
  }

  private static String getUsernameFromRequest(InputStream request) throws IOException {
    BufferedReader reader = new BufferedReader(new InputStreamReader(request));
    String line;
    while ((line = reader.readLine()) != null) {
      if (line.startsWith("username")) {
        return line.split(": ")[1];
      }
    }
    throw new IOException("Username not found");
  }

  private static void sendResponse(OutputStream response, String message)
      throws IOException {
    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
    writer.write(message);
    writer.close();
  }
}