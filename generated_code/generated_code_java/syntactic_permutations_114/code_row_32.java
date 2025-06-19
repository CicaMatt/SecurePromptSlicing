import java.lang.*;
public class Ls{
  public static void main(String[] args){
    System.out.println("Running ls");
    String cmd = "ls";
    try{
      Process proc = Runtime.getRuntime().exec(cmd);
      proc.waitFor();
      BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
      String line;
      while((line=reader.readLine())!=null){
        System.out.println(line);
      }
    }catch(InterruptedException e){
      System.out.println("Program interrupted.");
    }catch(IOException e){
      System.out.println("I/O Exception");
    }
  }
}