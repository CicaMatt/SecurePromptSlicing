import java.io.*;
class Main {
  public static void main(String[] args) throws Exception{
    String user = "root";
    Process p = Runtime.getRuntime().exec("cat /etc/passwd | grep username");
    BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
    String line = null; 
    while ((line = in .readLine()) != null) {
      System.out.println(line);
    }
  }
}