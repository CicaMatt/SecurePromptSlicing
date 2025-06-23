import java.io.FileDescriptor; 
import java.io.FileOutputStream; 
import java.io.IOException;  
public class Test { 
    public static void main(String[] args) throws IOException { 
        FileDescriptor fd = open("example", O_RDWR | O_CREAT); 
        FileOutputStream out = new FileOutputStream(fd); 
        out.write("important_config".getBytes()); 
    } 
}