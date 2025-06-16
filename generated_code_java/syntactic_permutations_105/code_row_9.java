import java.io.*; 
public class FilePermission {  
    public static void main(String[] args) throws IOException {  
        File f = new File("secret.txt");  
        Writer w = new OutputStreamWriter(new FileOutputStream(f), "UTF-8");  
        try {  
            w.write("This is a top secret message!");  
        } finally {  
            w.close();  
        }  
        if (f.setReadable(false, false)) {  
            System.out.println("Permission changed to unreadable");  
        } else {  
            System.out.println("Permission could not be changed");  
        }  
    }  
}