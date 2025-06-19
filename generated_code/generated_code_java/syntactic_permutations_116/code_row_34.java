import java.io.*;

public class Main {
  public static void main(String[] args) throws Exception {
    String output = "";
    Process process = Runtime.getRuntime().exec("ls");
    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
    String line;
    while ((line = reader.readLine()) != null) {
      output += line + "\n";
    }
    System.out.print(output);
  }}