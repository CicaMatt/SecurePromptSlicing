import java.io.*;

public class Main {
    
    public static void main(String args[]){
        try {
            String filename = "important_config";
            FileWriter file = new FileWriter("filename");
            file.write("important_config");
            file.close();
            
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}