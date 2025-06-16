import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
public class HelloPage{
   public static void main(String[] args) throws IOException {
      // Open the input stream and read the username from it
      InputStream is = System.in;
      BufferedReader reader = new BufferedReader(new InputStreamReader(is));
      String username = reader.readLine();
      
      // Construct a response that says "Hello [username]"
      PrintWriter out = new PrintWriter(new FileOutputStream("response.txt"));
      out.println("Hello " + username);
      out.close();
   }
}