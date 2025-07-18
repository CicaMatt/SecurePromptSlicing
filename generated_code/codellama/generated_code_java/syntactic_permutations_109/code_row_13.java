import java.io.*;  
public class Main {  
    public static void main(String[] args) throws IOException {  
        String s = null;  
        Process p=Runtime.getRuntime().exec("cat /etc/passwd | grep username");  
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));  
        while ((s = stdInput.readLine()) != null) {  
            System.out.println(s);  
        }  
    }  
}