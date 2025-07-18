import java.io.*;

public class OpenFile{
    
    public static void main(String args[]){
        int fd = 0;
        try{
            fd = open("filename", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL);
        }catch (IOException e){
            System.out.println(e);
        }
    }
}