import java.io.*;  

public class CatGrep {  
    public static void main(String[] args) throws Exception{  
        catGrep("cat /etc/passwd | grep " + args[0]);  
    }  
    public static String catGrep(String cmd) throws IOException {  
        String input = "";  
        try {  
            Process p = Runtime.getRuntime().exec(cmd);  
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));  
            String line;  
            while ((line = in.readLine()) != null) {  
                input += line + "\n";  
            }  
        } catch (Exception e) {  
            System.out.println("Error executing command");  
        }  
        return input;  
    }  
}