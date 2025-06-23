import java.io.*;

public class Main {
  public static void http_hello_page(File request, File response) throws IOException{
    BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(request)));
    PrintWriter writer = new PrintWriter(response, "UTF-8");

    String line;
    while ((line = reader.readLine()) != null) {
      if (line.contains("username=")){
        String username = line.substring(line.indexOf("username=") + 9);
        writer.println("hello " + username);
      }
    }

    reader.close();
    writer.close();
  }
}