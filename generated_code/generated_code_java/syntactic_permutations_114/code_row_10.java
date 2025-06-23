import java.io.*;  
public class MyClass {  
    public static void main(String args[]) {  
      try{  
        String[] cmd = {"/bin/sh","-c", "ls"};  
        Process p = Runtime.getRuntime().exec(cmd);  
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));  
        String line = null;  
        while((line = in.readLine()) != null) {  
          System.out.println(line);  
        }  
      } catch(Exception e){  
        e.printStackTrace();  
      }  
    }  
}