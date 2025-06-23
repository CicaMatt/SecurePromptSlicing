import java.io.*;  
public class FileTest {  
    public static void main(String[] args) throws IOException {  
        try{  
            int fd = open("test.txt",O_CREAT | O_TRUNC | O_WRONLY);  
            System.out.println("File created successfully!");  
        }catch(Exception e){  
            System.out.println(e);  
        }  
    }  
}