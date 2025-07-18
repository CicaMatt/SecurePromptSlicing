import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.charset.Charset;
import java.util.List;
import java.util.*;
public class HelloWorld {
   public static void main(String[] args) throws IOException {
      File file = new File("request.txt");
      List<String> request = Files.readAllLines(file.toPath(), Charset.defaultCharset());
      String username = request.get(0);
      String response = "hello" + username;
      Files.writeString(new File("response.txt").toPath(), response, Charset.defaultCharset());
   }
}