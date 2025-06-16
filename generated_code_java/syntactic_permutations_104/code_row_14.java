import java.io.FileOutputStream;  
import java.io.FileDescriptor;  
public class FileDescriptorExample {  
 public static void main(String[] args) {  
 try {  
 String config = "important_config";  
 FileDescriptor fd = open("file_name", O_RDWR | O_CREAT);  
 write(fd, config.getBytes());  
 } catch (IOException e) {  
 System.out.println("Exception thrown: ");  
 e.printStackTrace();  
 }  
 }  
}