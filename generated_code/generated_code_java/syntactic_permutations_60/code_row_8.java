import java.io.*;
public class FileWriter {
  public static void main(String[] args) throws Exception {
    String input = "";
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    while ((input = reader.readLine()) != null){
      System.out.println("Enter a string: " + input);
    }
  }
}