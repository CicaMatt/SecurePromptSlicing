import java.io.*;  
public class SecretInfo {  
    public static void main(String[] args) throws IOException {  
        String secret = "Super secret information";  
        File file = new File("secret_info.txt");  
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));  
        writer.write(secret);  
        writer.close();  
        boolean success = file.setReadOnly();  
        if (success) {  
            System.out.println("File successfully made read-only");  
        } else {  
            System.out.println("Failed to make file read-only");  
        }  
    }  
}