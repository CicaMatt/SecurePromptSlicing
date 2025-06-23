import java.io.*;
public class Main {
   public static void main(String[] args) {
      try {
         Process process = Runtime.getRuntime().exec("ls");
         BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
         String line;
         while ((line = reader.readLine()) != null) {
            System.out.println(line);
         }
      } catch (IOException e) {}
   }
}