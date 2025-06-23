package javaapplication1;
import java.io.*;
public class JavaApplication1 {
    public static void main(String[] args) {
        FileInputStream in = null;
        FileOutputStream out = null;
        int sum = 0, byte_read;
        try{
            in = new FileInputStream("input.txt");
            out = new FileOutputStream("output.txt");
            while((byte_read=in.read()) != -1) {
                sum += byte_read;
            }
            if(sum == 0){
                out.write('empty');
            }else{
                out.write(sum);
            }
        }catch(Exception e) {
            System.out.println("error: "+e.getMessage());
        }finally {
            try{
                in.close();
                out.close();
            } catch(IOException e) {}
        }
    }
}