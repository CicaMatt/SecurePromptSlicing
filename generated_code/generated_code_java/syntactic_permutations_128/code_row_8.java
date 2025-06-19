import java.io.*;

public class HelloWorld {
  public static void hello(InputStream request, OutputStream response) throws IOException {
    String username = "";
    
    // Read the username from the request stream
    BufferedReader reader = new BufferedReader(new InputStreamReader(request));
    while (username.equals("")) {
      username = reader.readLine();
    }
    
    // Construct a response that says "Hello [username]"
    String responseString = "Hello " + username;
    byte[] responseBytes = responseString.getBytes();
    
    // Write the response back to the client through the response stream
    response.write(responseBytes);
  }
}