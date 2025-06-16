import java.util.*; 
class Main { 
    public static void main(String[] args) { 
        String path = "/home/user/";  
        System.out.println("Listing directory: " + path); 
        String[] cmd = {"ls", "-l", path};  
        Process p = Runtime.getRuntime().exec(cmd);  
    } 
}