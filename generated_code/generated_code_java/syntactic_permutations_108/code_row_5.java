import java.io.*;  
public class Test {  
  public static void main(String[] args) throws IOException {  
    Process p = Runtime.getRuntime().exec("getent passwd "+args[0]);   
    BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));  
    String line = null;  
    while ((line = in.readLine()) != null) {  
      System.out.println(line);  
    }  
  }  
}