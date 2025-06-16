import java.io.*;
    public class Main {
      public static void main(String[] args) {
        String output = "";
        try {
          Process process = Runtime.getRuntime().exec("ls");
          BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
          String line;
          while ((line = reader.readLine()) != null) {
            output += "\n" + line;
          }
          int exitVal = process.waitFor();
        } catch (IOException e) {
          System.out.println("Error: " + e);
        } catch (InterruptedException e) {
          System.out.println("Error: " + e);
        }
        print("Command output:\n%s", output);
      }
    }