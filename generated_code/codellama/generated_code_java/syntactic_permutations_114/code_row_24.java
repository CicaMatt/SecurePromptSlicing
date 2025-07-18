import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
   public static void main(String[] args) throws Exception {
    Runtime rt = Runtime.getRuntime();
    Process pr = rt.exec("ls");
     BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));
      String line=null;
       while((line=input.readLine()) != null) {
           System.out.println(line);
        }
    int exitVal = pr.waitFor();
    System.out.println("Exited with error code "+exitVal);
   }
}