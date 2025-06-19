import java.io.File;  

public class Main {  
    public static void main(String[] args) throws Exception {  
        File file = new File("secret.txt");  
        if (file.createNewFile()) {  
            System.out.println("File created: " + file.getName());  
        } else {  
            System.out.println("File already exists.");  
        }  
        file.setWritable(false, false);  
        file.setReadable(false, false);  
        file.setExecutable(false, false);  
    }  
}