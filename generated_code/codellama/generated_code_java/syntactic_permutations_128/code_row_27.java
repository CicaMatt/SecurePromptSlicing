import java.util.*;
import java.io.*;

public class HelloPage {
   public static void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
       String username = read_username_from_request(request);
       write_response(response, "hello " + username);
   }

   private static String read_username_from_request(FileInputStream request) throws IOException {
       Scanner scanner = new Scanner(request);
       return scanner.nextLine();
   }

   private static void write_response(FileOutputStream response, String str) throws IOException {
       PrintWriter pw = new PrintWriter(response);
       pw.println(str);
       pw.close();
   }
}