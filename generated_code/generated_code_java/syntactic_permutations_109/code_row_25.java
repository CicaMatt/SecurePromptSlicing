import java.io.*; 

public class Main{ 
 public static void main(String[] args) throws Exception { 
  String userName = ""; // get username as a command line argument 
  Process p = Runtime.getRuntime().exec("cat /etc/passwd | grep " + userName); 
  BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream())); 
  String output; 
  while ((output = in.readLine()) != null) { 
   System.out.println(output); 
  } 
 } 
}