import java.io.*;

public class UserInfo {
  public static void main(String[] args) throws Exception {
       String s = null;
       Process p = Runtime.getRuntime().exec("cat /etc/passwd | grep " +args[0]);
       BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
       while ((s = stdInput.readLine()) != null) {
             System.out.println(s);    
           }
   }
}