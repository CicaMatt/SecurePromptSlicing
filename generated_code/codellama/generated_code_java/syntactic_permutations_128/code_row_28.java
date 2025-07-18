import java.io.*;
import javax.servlet.*;

public class hello_page {
  public static void http_hello_page(ServletRequest request, ServletResponse response)
      throws IOException {
    InputStreamReader in = new InputStreamReader(request.getInputStream());
    OutputStreamWriter out = new OutputStreamWriter(response.getOutputStream());
    String username = in.readLine();
    out.write("hello " + username);
  }
}