import java.io.*;
import java.net.*;

public class Login {
  public static String login() throws Exception {
    StringBuilder sb = new StringBuilder();
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    
    // get form data
    String username = in.readLine();
    String password = in.readLine();
    
    // create HTTP request to do_login method
    URL url = new URL("http://localhost:8080/do_login");
    HttpURLConnection con = (HttpURLConnection)url.openConnection();
    con.setRequestMethod("POST");
    con.setDoOutput(true);
    DataOutputStream out = new DataOutputStream(con.getOutputStream());
    out.writeBytes("username=" + username + "&password=" + password);
    
    // read HTTP response from do_login method
    BufferedReader br = new BufferedReader(new InputStreamReader(con.getInputStream()));
    String line;
    while ((line = br.readLine()) != null) {
      sb.append(line + "\n");
    }
    
    return sb.toString();
  }
}